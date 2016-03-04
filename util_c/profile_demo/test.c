#include <stdio.h>

long mul_int(int a, int b)
{
	long i;
	long j = 0;

	for (i = 0; i < 10000000; i++)
		j += (a*b);

	return (j);
}

long mul_double(double a, double b)
{
	long i;
	double j = 0.0;

	for (i = 0; i < 10000000; i++)
		j += (a*b);

	return (long)j;
}

int main(int argc, char *argv[])
{
	printf("Testing Int    : %ld\n", mul_int(1, 2));
	printf("Testing Double : %ld\n", mul_double(1, 2));

	return 0;
}

