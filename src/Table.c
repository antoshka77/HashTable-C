#include "Table.h"

int HashFunction(int size, int sizeLine)
{
	return (sizeLine % size);
}

List** Init(int size)
{
	List** head = (List**)malloc(size * sizeof(List*));//Создание динамического массива списков (первая строка хэш таблицы)
	int i;
	//Для каждого элемента первой строки хэш таблицы выделяем память под список, куда кладём элементы, подходящие по коду хэш функции
	for (i = 0; i < size; i++)
	{
		head[i] = (List*)malloc(size * sizeof(List));
		head[i] = NULL;
	}
	return head;
}

List* CreateKnot(char* key, int size)
{
	
	int sizeLine = HashFunction(size, strlen(key));
	List* ptr = (List*)malloc(sizeof(List));
	ptr->sizeLine = sizeLine;
	ptr->key = (char*)malloc((strlen(key) + 1) * sizeof(char));
	strcpy(ptr->key, key);
	ptr->next = NULL;
	return ptr;
}

List** Add(List* knot, List** head)
{
	List* ptr;
	ptr = head[knot->sizeLine];
	if (ptr == NULL) 
		head[knot->sizeLine] = knot; 
	else 
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = knot; 
	}
	return head;
}

List** Delete(char* key, List** head, int size)
{
	int sizeLine = HashFunction(size, strlen(key));
	List *current, *previous;
	previous = NULL;
	current = head[sizeLine];
	while (current) 
	{
		if (strcmp(current->key, key) == 0) 
		{
			if (current == head[sizeLine])
			{
				if (head[sizeLine]->next == NULL)
				{
					free(current->key);
					free(current);
					head[sizeLine] = NULL;
					return head;
				}
				head[sizeLine] = current->next;
				free(current->key);
				free(current);
				current = head[sizeLine];
			}
			else
			{
				if (current->next != NULL)
				{
					previous->next = current->next;
					free(current->key);
					free(current);
					current = previous->next;
				}
				else
				{
					previous->next = NULL;
					free(current->key);
					free(current);
					return head;
				}
			}
		}
		previous = current;
		current = previous->next;
	}
	if (head[sizeLine] == current)
		head[sizeLine] = current;
	return head;
}

int Search(char* key, List** head, int size, int mod)
{
	int sizeLine = HashFunction(size, strlen(key));
	List* ptr;
	int count = 0;
	ptr = head[sizeLine];
	if (mod == 1) 
		printf("Key for search: %s. ", key);
	while (ptr)
	{
		if (strcmp(ptr->key, key) == 0)
		{
			if (mod == 1)
				printf("Result of search is true Square coordinates: [%d; %d].\n", sizeLine, count);
			return 1;
		}
		ptr = ptr->next;
		count++;
	}
	if (mod == 1)
		printf("Reuslt of search is false.\n");
	return 0;
}

void Destruct(List** head, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		while (head[i])
			head = Delete(head[i]->key, head, size);
		free(head[i]);
	}
	free(head);
}

void PrintTable(List** head, int size, FILE* fileout)
{
	int i, j;
	List* ptr;
	fprintf(fileout, "____________________________________________\n");
	fprintf(fileout, "Size of table: %d", size);
	for (i = 0; i < size; i++)
	{
		fprintf(fileout, "\n\nSquare %d is ", i);
		ptr = head[i];
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

List** Rebuild(List** head, int sizePrev, int sizeNew)
{
	List** headNew = Init(sizeNew);
	List *ptrCur;
	int i;
	if (sizePrev == sizeNew)
	{
		Destruct(headNew, sizeNew);
		return head;
	}
	else
	{
		for (i = 0; i < sizePrev; i++)
		{
			ptrCur = head[i];
			while (ptrCur)
			{
				headNew = Add(CreateKnot(ptrCur->key, sizeNew), headNew);
				ptrCur = ptrCur->next;
			}
		}
	}
	Destruct(head, sizePrev);
	return headNew;
}

int Equals(List** head1, int size1, List** head2, int size2)
{
	int i;
	int countSame = 0;
	int count1 = Count(head1, size1);
	int count2 = Count(head2, size2);
	List* ptr;
	if ((size1 != size2) || (count1 != count2))
		return 0;
	else
	{
		for (i = 0; i < size1; i++)
		{
			ptr = head1[i];
			while (ptr)
			{
				countSame += Search(ptr->key, head2, size2, 0);
				ptr = ptr->next;
			}
		}
	}
	if (countSame == count1)
		return 1;
	return 0;
}

int Count(List** head, int size)
{
	int i, count = 0;
	List* ptr;
	for (i = 0; i < size; i++)
	{
		ptr = head[i];
		while (ptr)
		{
			count++;
			ptr = ptr->next;
		}
	}
	return count;
}

