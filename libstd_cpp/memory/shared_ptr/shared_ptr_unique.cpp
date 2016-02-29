#include "memory.h"
#include <iomanip>
#include <iostream>

typedef Hx::shared_ptr<int> spi;

int main()
{
	std::cout << std::boolalpha;
	spi sp0;
	std::cout << "empty object: " << sp0.unique() << '\n';
	spi sp1((int *) 0);
	std::cout << "null pointer: " << sp1.unique() << '\n';
	spi sp2(new int);
	std::cout << "one object: " << sp2.unique() << '\n';
	{
		spi sp3(sp2);
		std::cout << "two object: " << sp2.unique() << '\n';
	}
	std::cout << "one object: " << sp2.unique() << '\n';
	return 0;
}
