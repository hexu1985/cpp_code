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

void test_shared_ptr()
{
	boost::shared_ptr<Simple> pSimple(new Simple);
	boost::shared_ptr<Simple> pSimple2(pSimple);
	boost::shared_ptr<Simple> pSimple3 = pSimple;

	pSimple->foo();
	pSimple2->foo();
	pSimple3->foo();

	cout << "use count is: " << pSimple.use_count() << endl;
	pSimple2.reset();
	cout << "use count is: " << pSimple.use_count() << endl;
	pSimple3.reset();
	cout << "use count is: " << pSimple.use_count() << endl;
	pSimple.reset();

	cout << "exit shared_ptr_func()" << endl;
}

int main()
{
	test_shared_ptr();
	cout << "exit main()" << endl;

	return 0;
}
