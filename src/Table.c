#include "Table.h"



int HashFunction(char* key)
{
	int i = 0;
	int h = 0;
	while (key[i] != '\0')
	{
		h += T[0 ^ key[i]];
		i++;
	}
	return h;
}

HashTable Init(int initialSize)
{
	HashTable table;
	table.head = (List**)malloc(initialSize * sizeof(List*));//Создание динамического массива списков (первая строка хэш таблицы)
	int i;
	//Для каждого элемента первой строки хэш таблицы выделяем память под список, куда кладём элементы, подходящие по коду хэш функции
	for (i = 0; i < initialSize; i++)
	{
		table.head[i] = (List*)malloc(sizeof(List));
		table.head[i] = NULL;
	}
	table.size = initialSize;
	table.count = (int*)malloc(sizeof(int));
	table.count[0] = 0;
	return table;
}


HashTable Add(HashTable h, char* toAdd)
{
	int sizeLine = HashFunction(toAdd) % h.size;
	List* ptr = (List*)malloc(sizeof(List)); //создаваемый узел
	List* node;
	ptr->sizeLine = sizeLine;
	ptr->key = (char*)malloc((strlen(toAdd) + 1) * sizeof(char));
	strcpy(ptr->key, toAdd);
	ptr->next = NULL;
	node = h.head[sizeLine];
	if (node == NULL) 
		h.head[sizeLine] = ptr;
	else 
	{
		while (node->next != NULL)
			node = node->next;
		node->next = ptr; 
	}
	h.count[0]++;
	if (h.count[0] == h.size)
		h = Rebuild(h);
	return h;
}

void Delete(HashTable h, char* toDelete)
{
	int sizeLine = HashFunction(toDelete) % h.size;
	List *current, *previous;
	previous = NULL;
	current = h.head[sizeLine];
	int flag = 0;
	while (current)
	{
		if (strcmp(current->key, toDelete) == 0)
		{
			if (current == h.head[sizeLine])
			{
				if (h.head[sizeLine]->next == NULL)
				{
					free(current->key);
					free(current);
					h.head[sizeLine] = NULL;
					flag = 1;
					h.count[0]--;
					return;
				}
				h.head[sizeLine] = current->next;
				free(current->key);
				free(current);
				flag = 1;
				current = h.head[sizeLine];
			}
			else
			{
				if (current->next != NULL)
				{
					previous->next = current->next;
					free(current->key);
					free(current);
					flag = 1;
					current = previous->next;
				}
				else
				{
					previous->next = NULL;
					free(current->key);
					free(current);
					flag = 1;
					h.count[0]--;
					return;
				}
			}
		}
		previous = current;
		current = previous->next;
	}
	if (h.head[sizeLine] == current)
		h.head[sizeLine] = current;
	if (flag == 1)
		h.count[0]--;
}

int Search(HashTable h, char* key)
{
	int sizeLine = HashFunction(key) % h.size;
	List* ptr;
	ptr = h.head[sizeLine];
	while (ptr)
	{
		if (strcmp(ptr->key, key) == 0)
			return 1;
		ptr = ptr->next;
	}
	return 0;
}

void Destruct(HashTable h)
{
	int i;
	for (i = 0; i < h.size; i++)
	{
		while (h.head[i])
			Delete(h, h.head[i]->key);
		free(h.head[i]);
	}
	free(h.head);
	free(h.count);
}

void PrintTable(HashTable h, FILE* fileout)
{
	int i, j;
	List* ptr;
	fprintf(fileout, "____________________________________________\n");
	fprintf(fileout, "Size of table: %d", h.size);
	for (i = 0; i < h.size; i++)
	{
		fprintf(fileout, "\n\nSquare %d is ", i);
		ptr = h.head[i];
		if (ptr != NULL)
		{
			j = 0;
			fprintf(fileout, "\n%d) %s", j, ptr->key);
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
				j++;
				fprintf(fileout, "\n%d) %s", j, ptr->key);
			}
		}
		else
			fprintf(fileout, "empty");
	}
	fprintf(fileout, "\n____________________________________________\n");
}


int Equals(HashTable h1, HashTable h2)
{
	int i;
	int countSame = 0;
	List* ptr;
	if ((h1.size != h2.size) || (h1.count[0] != h2.count[0]))
		return 0;
	else
	{
		for (i = 0; i < h1.size; i++)
		{
			ptr = h1.head[i];
			while (ptr)
			{
				countSame += Search(h2, ptr->key);
				ptr = ptr->next;
			}
		}
	}
	if (countSame == h1.count[0])
		return 1;
	return 0;
}

HashTable Rebuild(HashTable h)
{
	HashTable headNew = Init(2 * h.size);
	List *ptrCur;
	int i;
	for (i = 0; i < h.size; i++)
	{
		ptrCur = h.head[i];
		while (ptrCur)
		{
			Add(headNew, ptrCur->key);
			ptrCur = ptrCur->next;
		}
	}
	Destruct(h);
	return headNew;
}