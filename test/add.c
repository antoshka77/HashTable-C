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
	assert_equals_int(8, Count(head, size));
}