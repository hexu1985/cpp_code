#include <iostream>
#include <iomanip>
#include "thread.h"
#include "chrono.h"

void foo()
{
	Hx::this_thread::sleep_for(Hx::chrono::seconds(1));
}

int main()
{
	Hx::thread t1(foo);
	Hx::thread::id t1_id = t1.get_id();

	Hx::thread t2(foo);
	Hx::thread::id t2_id = t2.get_id();

	std::cout << std::hex << std::showbase;
	std::cout << "t1's id: " << t1_id << '\n';
	std::cout << "t2's id: " << t2_id << '\n';
	std::cout << std::dec << std::noshowbase;

	t1.join();
	t2.join();
	return 0;
}

/*
Possible output: 

t1's id: 0x35a7210f
t2's id: 0x35a311c4
*/

