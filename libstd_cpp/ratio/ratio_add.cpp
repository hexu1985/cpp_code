// ratio_add example
#include <iostream>
#include "ratio.h"

int main ()
{
	typedef Hx::ratio<1,2> one_half;
	typedef Hx::ratio<2,3> two_thirds;

	typedef Hx::ratio_add<one_half,two_thirds> sum;

	std::cout << "sum = " << sum::num << "/" << sum::den;
	std::cout << " (which is: " << ( double(sum::num) / sum::den ) << ")" << std::endl;

	return 0;
}


/*
Output:

sum = 7/6 (which is: 1.166667)
*/

