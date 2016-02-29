#include <boost/shared_ptr.hpp>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Simple {
private:
	size_t m_size;

public:
	Simple()
	{
		m_size = 10;
		cout << "Simple created" << endl;
	}

	~Simple()
	{
		cout << "Simple destroyed" << endl;
	}

	void foo()
	{
		cout << "foo() is called, m_size is: " << m_size << endl;
		m_size++;
	}
};

void shared_ptr_func()
{
	boost::shared_ptr<Simple> pSimple(new Simple);
	boost::shared_ptr<Simple> pSimple2(pSimple);
	boost::shared_ptr<Simple> pSimple3 = pSimple;

	pSimple->foo();
	pSimple2->foo();
	pSimple3->foo();

	cout << "exit shared_ptr_func()" << endl;
}

int main()
{
	shared_ptr_func();
	cout << "exit main()" << endl;

	return 0;
}
