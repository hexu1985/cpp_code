#include <iostream>
#if __cplusplus >= 201103L
#include <atomic>
#else
#include <csignal>
#endif

#include "condition_variable.h"
#include "thread.h"
#include "chrono.h"

Hx::condition_variable_any cv;
Hx::mutex cv_m;

#if __cplusplus >= 201103L
std::atomic<int> i = ATOMIC_VAR_INIT(0);
#else
volatile sig_atomic_t i = 0;
#endif
 
#if __cplusplus < 201103L
bool available () { return i == 1; }
#endif
 
void waits(int idx)
{
	cv_m.lock();
#if __cplusplus >= 201103L
	auto now = Hx::chrono::system_clock::now();
	if(cv.wait_until(cv_m, 
		now + Hx::chrono::milliseconds(idx*100), 
		[](){return i == 1;})) 
#else
	Hx::chrono::system_clock::time_point now = Hx::chrono::system_clock::now();
	if (cv.wait_until(cv_m, 
		now+Hx::chrono::system_clock::duration(Hx::chrono::milliseconds(idx*100)), 
		available))
#endif
		std::cerr << "Thread " << idx << " finished waiting. i == " << i << '\n';
	else
		std::cerr << "Thread " << idx << " timed out. i == " << i << '\n';
}
 
void signals()
{
	Hx::this_thread::sleep_for(Hx::chrono::milliseconds(120));
	std::cerr << "Notifying...\n";
	cv.notify_all();
	Hx::this_thread::sleep_for(Hx::chrono::milliseconds(100));
	i = 1;
	std::cerr << "Notifying again...\n";
	cv.notify_all();
}
 
int main()
{
	Hx::thread t1(waits, 1), t2(waits, 2), t3(waits, 3), t4(signals);
	t1.join(), t2.join(), t3.join(), t4.join();
}

/*
Possible output:

Thread 1 timed out. i == 0
Notifying...
Thread 2 timed out. i == 0
Notifying again...
Thread 3 finished waiting. i == 1
*/
