#include "test.h"
#include "Table.h"

void test()
{
	int size = 10;
	int count = 0;
	HashTable head;
	head = Init(size);
	head = Add(head, "a");
	head = Add(head, "as");
	head = Add(head, "asd");
	head = Add(head, "asdf");
	head = Add(head, "asdfg");
	head = Add(head, "asdfgh");
	head = Add(head, "asdfghj");
	head = Add(head, "asdfghjk");

	count += Search(head, "a");
	count += Search(head, "asd");
	count += Search(head, "asdfg");

	assert_equals_int(3, count);
}