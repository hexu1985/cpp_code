#include "thread.h"
#include <iostream>
#include "chrono.h"
#include "mutex.h"
#include <cerrno>
#include <cstring>
#include <pthread.h>
 
Hx::mutex iomutex;
void f(int num)
{
    Hx::this_thread::sleep_for(Hx::chrono::seconds(1));
 
   sched_param sch;
   int policy; 
   pthread_getschedparam(pthread_self(), &policy, &sch);
   Hx::lock_guard<Hx::mutex> lk(iomutex);
   std::cout << "Thread " << num << " is executing at priority "
             << sch.sched_priority << '\n';
}
 
int main()
{
    Hx::thread t1(f, 1), t2(f, 2);
 
    sched_param sch;
    int policy; 
    pthread_getschedparam(t1.native_handle(), &policy, &sch);
    sch.sched_priority = 20;
    if(pthread_setschedparam(t1.native_handle(), SCHED_FIFO, &sch)) {
        std::cout << "Failed to setschedparam: " << std::strerror(errno) << '\n';
    }
 
    t1.join(); t2.join();
}

/*
Output:

Thread 2 is executing at priority 0
Thread 1 is executing at priority 20
*/
