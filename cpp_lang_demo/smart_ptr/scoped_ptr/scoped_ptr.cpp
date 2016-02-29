#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>
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
		cout << "m_size is: " << m_size << endl;
		cout << "foo() is called" << endl;
	}
};

int main()
{
	boost::scoped_ptr<Simple> pSimple(new Simple);
	//boost::scoped_ptr<Simple> pSimple2(pSimple);	// 编译错误
	//boost::scoped_ptr<Simple> pSimple3 = pSimple;	// 编译错误
}
