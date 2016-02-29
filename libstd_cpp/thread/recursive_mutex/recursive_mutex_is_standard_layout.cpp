#include <iostream>
#include <type_traits>
#include "mutex.h"

int main()
{
	std::cout << "is_standard_layout: "
		<< std::is_standard_layout<Hx::recursive_mutex>::value
		<< "\n";
	return 0;
}

