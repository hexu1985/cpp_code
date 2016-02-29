#include <iostream>
#include "thread.h"
#include "mutex.h"
 
int g_i = 0;
Hx::mutex g_i_mutex;  // protects g_i
 
void safe_increment()
{
	Hx::lock_guard<Hx::mutex> lock(g_i_mutex);
	++g_i;
 
	// g_i_mutex is automatically released when lock
	// goes out of scope
}
 
int main()
{
	Hx::thread t1(safe_increment);
	Hx::thread t2(safe_increment);
 
	t1.join();
	t2.join();

	std::cout << "g_i: " << g_i << "\n";

	return 0;
}

/*
Output:
g_i: 2
*/
 
