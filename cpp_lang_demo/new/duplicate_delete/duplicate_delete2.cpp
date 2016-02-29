#include <stdio.h>
#include <string.h>

class Simple_class {
private:
	char *m_buf;
	size_t m_size;

public:
	Simple_class(size_t n=1) 
	{
		m_buf = new char[n];
		m_size = n;
	}

	~Simple_class() 
	{
		printf("%d is deleted at %x\n", m_size, m_buf);
		delete [] m_buf;
	}

	char *get_buf()
	{
		return m_buf;
	}

};

void foo()
{
	Simple_class a(10);
	Simple_class b = a;
	char *p = a.get_buf();

	strcpy(p, "Hello");
	printf("%s\n", p);
}

int main()
{
	foo();
	printf("exit main() ...\n");
}
