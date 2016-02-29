// ratio_equal example
#include <iostream>
#include "ratio.h"

int main ()
{
	typedef Hx::ratio<1,2> one_half;
	typedef Hx::ratio<2,4> two_fourths;

	std::cout << "1/2 == 2/4 ? " << std::boolalpha;
	std::cout << Hx::ratio_equal<one_half,two_fourths>::value << std::endl;

	return 0;
}


/*
Output:

1/2 == 2/4 ? true
*/

