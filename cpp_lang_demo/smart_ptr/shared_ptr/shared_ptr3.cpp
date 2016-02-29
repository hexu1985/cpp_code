#include <boost/smart_ptr.hpp>
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

void test_ptr()
{
	boost::shared_ptr<Simple> pSimple(new Simple);
	boost::weak_ptr<Simple> pSimple2(pSimple);

	pSimple.reset();
	
	if (pSimple2.lock())
		pSimple2.lock()->foo();
	else
		cout << "Simple is gone!" << endl;

	try {
		boost::shared_ptr<Simple> pSimple3 = pSimple;
		pSimple3->foo();
	} catch (boost::bad_weak_ptr) {
		cout << "Simple is gone, can not construct shared_ptr" << endl;
	}

	cout << "exit shared_ptr_func()" << endl;
}

int main()
{
	test_ptr();
	cout << "exit main()" << endl;

	return 0;
}
