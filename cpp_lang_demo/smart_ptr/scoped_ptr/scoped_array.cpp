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

void boost_array()
{
	boost::scoped_array<Simple> pSimple(new Simple[2]);
}

void auto_ptr_array()
{
	std::auto_ptr<Simple> pSimple(new Simple[2]);
}

int main()
{
	cout << "-------------- calling boost_array() ----------------" << endl;
	boost_array();
	cout << "-------------- boost_array() finished ---------------" << endl;

	cout << "-------------- calling auto_ptr_array() -------------" << endl;
	auto_ptr_array();
	cout << "-------------- auto_ptr_array() finished ------------" << endl;

	return 0;
}
