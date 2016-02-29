#include "memory.h"
#include <iostream>

typedef Hx::shared_ptr<int> spi;

int main()
{
	spi sp0;
	std::cout << "empty object: " << sp0.use_count() << '\n';
	spi sp1((int *) 0);
	std::cout << "null pointer: " << sp1.use_count() << '\n';
	spi sp2(new int);
	std::cout << "one object: " << sp2.use_count() << '\n';
	{
		spi sp3(sp2);
		std::cout << "two object: " << sp2.use_count() << '\n';
	}
	std::cout << "one object: " << sp2.use_count() << '\n';
	return 0;
}
