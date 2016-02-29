#include <stdio.h>
#include <string.h>

class Simple_class {
private:
	char *m_buf;
	size_t m_size;
	int *m_count;

public:
	Simple_class(size_t n=1) 
	{
		m_buf = new char[n];
		m_size = n;

		m_count = new int;
		*m_count = 1;
		printf("count is: %d\n", *m_count);
	}

	Simple_class(const Simple_class &s)
	{
		m_size = s.m_size;
		m_buf = s.m_buf;
		m_count = s.m_count;

		(*m_count)++;
		printf("count is: %d\n", *m_count);
	}

	~Simple_class() 
	{
		(*m_count)--;
		printf("count is: %d\n", *m_count);
		if (*m_count == 0) {
			printf("%d is deleted at %x\n", m_size, m_buf);
			delete [] m_buf;
			delete m_count;
		}
	}

	char *get_buf()
	{
		return m_buf;
	}

};

void foo()
{
	Simple_class a(10);
	char *p = a.get_buf();

	strcpy(p, "Hello");
	printf("%s\n", p);

	Simple_class b = a;
	Simple_class c(20);
	c = a;
	printf("b=%s, c=%s\n", b.get_buf(), c.get_buf());
}

int main()
{
	foo();
	printf("exit main() ...\n");
}
