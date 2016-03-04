#include <iostream>

using namespace std;

struct Test {
	int a,b,c,d;
};

int test_ptr(Test *ptr)
{
	int sum = 0;

	sum += ptr->a;
	sum += ptr->b;
	sum += ptr->c;
	sum += ptr->d;

	return sum;
}

int test_ref(const Test &ref)
{
	int sum = 0;

	sum += ref.a;
	sum += ref.b;
	sum += ref.c;
	sum += ref.d;

	return sum;
}

int main()
{
	Test test = {1, 2, 3, 4};

	int sum = 0;
	sum += test.a;
	sum += test.b;
	sum += test.c;
	sum += test.d;

	cout << sum << endl;

	sum += test_ptr(&test);

	cout << sum << endl;

	sum += test_ref(test);

	cout << sum << endl;

	return 0;
}
