#include "Table.h"

char* ReadLine(int* flag)
{
	char symb; 
	char *string = (char*)malloc(0);
	int shift = 1;
	symb = (char)fgetc(stdin);
	shift++;
	string = (char*)realloc(string, shift);
	string[shift - 2] = symb;
	while (symb != '\n')
	{
		if (symb == EOF)
		{
			*flag = 1;
			break;
		}
		symb = (char)fgetc(stdin);
		shift++;
		string = (char*)realloc(string, shift);
		string[shift - 2] = symb;
	}
	if (*flag != 1)
		string[shift - 3] = '\0';
	else
		string[shift - 2] = '\0';
	return string;
}

int main(int argc, char* argv[])
{
	char* string = NULL;
	FILE *filein;
	FILE *fileout;
	List** head = NULL;
	int size = 0;
	int* flag = (int*)malloc(sizeof(int));
	*flag = 0;
	if (argc > 3)
	{
		printf("ERROR: many arguments\n");
		return 101;
	}
	if (argc == 3)
	{
		filein = freopen(argv[1], "r", stdin);
		fileout = fopen(argv[2], "w");
		if (filein == NULL)
		{
			printf("ERROR: file is not open\n");
			return 911;
		}
		else
		{
			string = ReadLine(flag);
			size = atoi(string);
			head = Init(size);
			while (*flag != 1)
			{
				free(string);
				string = ReadLine(flag);
				fprintf(fileout, "%s %d\n", string, strlen(string));
				head = Add(CreateKnot(string, size), head);
			}
			PrintTable(head, size, fileout);
			Destruct(head, size);
		}
	}
	return 0;
}