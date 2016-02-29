#include "memory.h"
#include <iostream>

int main()
{
	int *ip = new int(3);
	std::cout << (void *) ip << '\n';
	Hx::shared_ptr<int> sp(ip);
	std::cout << (void *) sp.get() << '\n';
	Hx::shared_ptr<int> sq;
	std::cout << (void *) sq.get() << '\n';

	return 0;
}
