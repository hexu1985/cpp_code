#include <string>
#include <iostream>
#include "memory.h"

typedef std::basic_string<char, std::char_traits<char>, Hx::allocator<char> >
	string_type;

int main()
{
	Hx::allocator<char> alloc;
	string_type a("hello", alloc);
	std::cout << a << "\n";
	return 0;
}
