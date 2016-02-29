#include <stdio.h>
#include <new>

using namespace std;

void *operator new[](std::size_t n, char *file, int line)
{
	printf("size: %d\nnew at %s, %d\n", n, file, line);
	return ::operator new(n);
}

void operator delete[](void *p, char *file, int line)
{
	printf("delete at %s, %d\n", file, line);
	::operator delete(p);
	return;
}

#define new new(__FILE__, __LINE__)

int main()
{
	char *p = new char[10];

	operator delete [](p, __FILE__, __LINE__);
	return 0;
}
