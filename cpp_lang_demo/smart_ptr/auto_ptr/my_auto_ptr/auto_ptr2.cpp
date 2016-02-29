#include <string>
#include <iostream>
#include "my_auto_ptr.h"

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
	Auto_ptr<string> pString(new string("Hello, auto ptr"));
	cout << *pString << endl;	// 正常输出
	Auto_ptr<string> pString2(pString);
	cout << *pString << endl;	// 出错
	
	Auto_ptr<Simple> pSimple(new Simple());
	pSimple->foo();

	return 0;
}
