#include <stdio.h>
#include <new>

using namespace std;

int main()
{
	char buffer[100];
	char *p = new(buffer) char[20];

	printf("buffer:\t%x\np:\t%x\n", buffer, p);
	return 0;
}
