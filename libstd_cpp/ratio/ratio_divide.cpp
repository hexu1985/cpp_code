// ratio_divide example
#include <iostream>
#include "ratio.h"

int main ()
{
	typedef Hx::ratio<1,2> one_half;
	typedef Hx::ratio<1,3> one_third;

	typedef Hx::ratio_divide<one_half,one_third> result;

	std::cout << "result = " << result::num << "/" << result::den;
	std::cout << " (which is: " << ( double(result::num) / result::den ) << ")" << std::endl;

	return 0;
}


/*
Output:

result = 3/2 (which is: 1.5)
*/

