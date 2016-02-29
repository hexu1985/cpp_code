#include <iostream>
#include "mutex.h"

using namespace Hx;
 
int main()
{
	recursive_timed_mutex test;
	if (test.try_lock()==true)
		std::cout << "lock acquired" << std::endl;
	else
		std::cout << "lock not acquired" << std::endl;
	test.unlock();	//now unlock the mutex
	test.lock();	//to lock it again
	if (test.try_lock())  //true can be left out
		std::cout << "lock acquired" << std::endl;
	else
		std::cout << "lock not acquired" << std::endl;
	test.lock(); //and now the finale (a block)
	return 0;
}

/*
Output:

lock acquired
lock lock acquired
*/
