#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List List;

typedef struct List{
	int sizeLine; //остаток от деления длины строки на размер хэш таблицы
	char* key; //указатель на строку
	List* next; //указатель на следующий элемент структуры
}List;

int HashFunction(int size, int sizeLine);
List** Init(int size);
List* CreateKnot(char* key, int size);
List** Add(List* knot, List** head);
List** Delete(char* key, List** head, int size);
int Search(char* key, List** head, int size, int mod);
void Destruct(List** head, int size);
void PrintTable(List** head, int size, FILE* fileout);
List** Rebuild(List** head, int sizePrev, int sizeCur);
int Count(List** head, int size);
int Equals(List** head1, int size1, List** head2, int size2);