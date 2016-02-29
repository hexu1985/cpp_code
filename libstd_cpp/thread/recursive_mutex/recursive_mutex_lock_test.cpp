#include <iostream>
#include "chrono.h"
#include "thread.h"
#include "mutex.h"

int g_num = 0;  // protected by g_num_mutex
Hx::recursive_mutex g_num_mutex;
 
void slow_increment(int id) 
{
    for (int i = 0; i < 3; ++i) {
        g_num_mutex.lock();
        ++g_num;
        std::cout << id << " => " << g_num << '\n';
        g_num_mutex.unlock();
 
        Hx::this_thread::sleep_for(Hx::chrono::seconds(1));
    }
}
 
int main()
{
	Hx::thread t1(slow_increment, 0);
	Hx::thread t2(slow_increment, 1);
	t1.join();
	t2.join();
}

/*
Possible output:

0 => 1
1 => 2
0 => 3
1 => 4
0 => 5
1 => 6
*/
