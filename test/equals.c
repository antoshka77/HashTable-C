#include "test.h"
#include "Table.h"

void test()
{
	int size = 10;
	HashTable head1;
	head1 = Init(size);
	head1 = Add(head1, "a");
	head1 = Add(head1, "as");

	HashTable head2;
	head2 = Init(size);
	head2 = Add(head2, "a");
	head2 = Add(head2, "as");

	assert_equals_int(1, Equals(head1, head2));

	HashTable head3;
	head3 = Init(size);
	head3 = Add(head3, "a");

	HashTable head4;
	head4 = Init(size);
	head4 = Add(head4, "a");
	head4 = Add(head4, "as");

	assert_equals_int(0, Equals(head3, head4));

	HashTable head5;
	head5 = Init(size);
	head5 = Add(head5, "a");
	head5 = Add(head5, "as");

	HashTable head6;
	head6 = Init(size);
	head6 = Add(head6, "a");
	head6 = Add(head6, "asf");

	assert_equals_int(0, Equals(head5, head6));
}