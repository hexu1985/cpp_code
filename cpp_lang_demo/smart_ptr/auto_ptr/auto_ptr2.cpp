#include <string>
#include <iostream>
#include <memory>

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
	auto_ptr<string> pString(new string("Hello, auto ptr"));
	cout << *pString << endl;	// 正常输出
	auto_ptr<string> pString2(pString);
	cout << *pString << endl;	// 出错
	
	auto_ptr<Simple> pSimple(new Simple());
	pSimple->foo();

	return 0;
}
