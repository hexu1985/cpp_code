
#include <iostream>
#include "key_words.h"

#define ONE 1

struct A {
	static_assert(sizeof (char) == ONE, "sizeof (char) != 1");
	static_assert(sizeof (short) == sizeof (int), "sizeof (int) != sizeof (long)");
	static_assert(sizeof (long) == sizeof (int), "sizeof (int) != sizeof (long)");
};

int main()
{
	std::cout << "sizeof (long): " << sizeof (long) << std::endl;
	std::cout << "sizeof (int): " << sizeof (int) << std::endl;
	std::cout << "sizeof (short): " << sizeof (short) << std::endl;
	return 0;
}

