#include "memory.h"
#include <iostream>

int main()
{
	int *ip = new int(3);
	std::cout << (void *) ip << '\n';
	Hx::shared_ptr<int> sp(ip);
	std::cout << *sp << '\n';
	std::cout << (void *)&*sp << '\n';
	return 0;
}
