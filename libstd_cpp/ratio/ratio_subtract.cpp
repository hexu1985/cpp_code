// ratio_subtract example
#include <iostream>
#include "ratio.h"

int main ()
{
	typedef Hx::ratio<2,3> two_thirds;
	typedef Hx::ratio<1,2> one_half;

	typedef Hx::ratio_subtract<two_thirds,one_half> diff;

	std::cout << "diff = " << diff::num << "/" << diff::den;
	std::cout << " (which is: " << ( double(diff::num) / diff::den ) << ")" << std::endl;

	return 0;
}


/*
Output:

diff = 1/6 (which is: 0.166667)
*/

