#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List List;

typedef struct List{
	int sizeLine; //число получаемое хэш функцией
	char* key; //указатель на строку
	List* next; //указатель на следующий элемент структуры
}List;

typedef struct HashTable {
	List** head;
	int size;
	int *count;
}HashTable;

int HashFunction(char* key);
int Search(HashTable h, char* key);
void Destruct(HashTable h);
void PrintTable(HashTable h, FILE* fileout);
HashTable Rebuild(HashTable h);
int Equals(HashTable h1, HashTable h2);
HashTable Init(int initialSize);
HashTable Add(HashTable h, char* toAdd);
void Delete(HashTable h, char* toDelete);
