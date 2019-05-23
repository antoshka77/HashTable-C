#include "test.h"
#include "Table.h"

void test()
{
	int size = 10;
	List** head;
	int count = 0;
	head = Init(size);
	head = Add(CreateKnot("1", size), head);
	head = Add(CreateKnot("20", size), head);
	head = Add(CreateKnot("300", size), head);
	head = Add(CreateKnot("4000", size), head);
	head = Add(CreateKnot("50000", size), head);
	head = Add(CreateKnot("600000", size), head);
	head = Add(CreateKnot("7000000", size), head);
	head = Add(CreateKnot("80000000", size), head);

	count += Search("1", head, 10, 0);
	count += Search("7000000", head, 10, 0);
	count += Search("4000", head, 10, 0);

	assert_equals_int(3, count);
}