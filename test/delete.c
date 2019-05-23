#include "test.h"
#include "Table.h"

void test()
{
	int size = 10;
	List** head;
	head = Init(size);
	head = Add(CreateKnot("1", size), head);
	head = Add(CreateKnot("20", size), head);
	head = Add(CreateKnot("300", size), head);
	head = Add(CreateKnot("4000", size), head);
	head = Add(CreateKnot("50000", size), head);
	head = Add(CreateKnot("600000", size), head);
	head = Add(CreateKnot("7000000", size), head);
	head = Add(CreateKnot("80000000", size), head);

	head = Delete("1", head, size);
	head = Delete("600000", head, size);
	head = Delete("300", head, size);
	head = Delete("80000000", head, size);

	assert_equals_int(4, Count(head, size));
}