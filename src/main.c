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
	HashTable h1, h2;
	int size = 0;
	int eq = 0;
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
			printf("ERROR: file is empty\n");
			return 911;
		}
		else
		{
			string = ReadLine(flag);
			size = atoi(string);
			h1 = Init(size);
			h2 = Init(size);
			while (*flag != 1)
			{
				free(string);
				string = ReadLine(flag);
				fprintf(fileout, "%s %d\n", string, strlen(string));
				h1 = Add(h1, string);
				h2 = Add(h2, string);
			}
			eq = Equals(h1, h2);
			fprintf(fileout, "\n%d\n", eq);
			Delete(h1, "Xvc");
			eq = Equals(h1, h2);
			fprintf(fileout, "\n%d\n", eq);
			PrintTable(h1, fileout);
			h2 = Add(h2, "fdsg");
			PrintTable(h2, fileout);
			fprintf(fileout, "\n%d\n", Search(h1, "Xvc"));
			fprintf(fileout, "%d\n", Search(h1, "asdf"));
			Destruct(h1);
			Destruct(h2);

		}
	}
	return 0;
}