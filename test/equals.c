#include "test.h"
#include "Table.h"

void test()
{
	int size = 10;
	List** head1;
	head1 = Init(size);
	head1 = Add(CreateKnot("1", size), head1);
	head1 = Add(CreateKnot("20", size), head1);

	List** head2;
	head2 = Init(size);
	head2 = Add(CreateKnot("1", size), head2);
	head2 = Add(CreateKnot("20", size), head2);

	assert_equals_int(1, Equals(head1, size, head2, size));

	List** head3;
	head3 = Init(size);
	head3 = Add(CreateKnot("1", size), head3);

	List** head4;
	head4 = Init(size);
	head4 = Add(CreateKnot("1", size), head4);
	head4 = Add(CreateKnot("20", size), head4);

	assert_equals_int(0, Equals(head3, size, head4, size));

	List** head5;
	head5 = Init(size);
	head5 = Add(CreateKnot("1", size), head5);
	head5 = Add(CreateKnot("2", size), head5);


	List** head6;
	head6 = Init(size);
	head6 = Add(CreateKnot("1", size), head6);
	head6 = Add(CreateKnot("20", size), head6);

	assert_equals_int(0, Equals(head5, size, head6, size));
}