#include <iostream>
#include "mutex.h"
 
int main()
{
	Hx::recursive_timed_mutex test;
	if (test.try_lock()==true) {
		std::cout << "lock acquired" << std::endl;
		test.unlock();	//now unlock the mutex	
	} else {
		std::cout << "lock not acquired" << std::endl;
	}
 
	test.lock();	//to lock it again
	if (test.try_lock()) {  //true can be left out
		std::cout << "lock acquired" << std::endl;
	} else {
		std::cout << "lock not acquired" << std::endl;
	}
	test.unlock(); 
	test.unlock(); 

	return 0;
}

/*
Output:

lock acquired
lock acquired
*/
