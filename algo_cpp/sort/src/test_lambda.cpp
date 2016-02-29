#include <iostream>

using namespace std;

template <typename Test>
void run_test1(Test test)
{
	test();
}

template <typename Test>
void run_test2(Test &&test)
{
	test();
}

class A {
	int a;

public:
	A(): a(0)
	{
		cout << "Default constructor\n";
	}

	A(int x): a(x) 
	{
		cout << "Initial constructor\n";
	}

	A(const A &x): a(x.a) 
	{
		cout << "Copy constructor\n";
	}

	A(A&& x): a(x.a)
	{
		x.a = 0;
		cout << "Move constructor\n";
	}

	~A() { cout << "Destructor\n"; }

	void print() const { cout << "this: " << (void *) this << ": " << a << '\n'; }
};

int main()
{
	A a(3);

//	auto test1 = [a](){ a.print(); };
	cout << "run test1\n";
//	run_test1(test1);
	run_test1([a](){ a.print(); });
	cout << "--------------------------------\n";

//	auto test2 = [a](){ a.print(); };
	cout << "run test2\n";
//	run_test2(test2);
	run_test2([a](){ a.print(); });
	cout << "--------------------------------\n";

	return 0;
}
