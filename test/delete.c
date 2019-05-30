#include "test.h"
#include "Table.h"

void test()
{
	int size = 10;
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

	Delete(head, "a");
	Delete(head, "asdf");
	Delete(head, "asd");
	Delete(head, "asdfghj");

	assert_equals_int(4, head.count[0]);
}