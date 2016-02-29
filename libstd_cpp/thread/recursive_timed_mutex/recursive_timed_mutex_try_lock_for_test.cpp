// recursive_timed_mutex::try_lock_for example
#include <iostream>       // std::cout
#include "chrono.h"         // std::chrono::milliseconds
#include "thread.h"         // std::thread
#include "mutex.h"          // std::recursive_timed_mutex

Hx::recursive_timed_mutex mtx;

void fireworks () {
  // waiting to get a lock: each thread prints "-" every 200ms:
  while (!mtx.try_lock_for(Hx::chrono::milliseconds(200))) {
    std::cout << "-";
  }
  // got a lock! - wait for 1s, then this thread prints "*"
  Hx::this_thread::sleep_for(Hx::chrono::milliseconds(1000));
  std::cout << "*\n";
  mtx.unlock();
}

int main ()
{
#if __cplusplus >= 201103L
  Hx::thread threads[10];
#else
  Hx::thread *threads[10];
#endif

  // spawn 10 threads:
  for (int i=0; i<10; ++i)
#if __cplusplus >= 201103L
    threads[i] = Hx::thread(fireworks);
#else
    threads[i] = new Hx::thread(fireworks);
#endif 

#if __cplusplus >= 201103L
  for (auto& th : threads) th.join();
#else
  for (int i=0; i<10; ++i) {
    threads[i]->join();
    delete threads[i];
  }
#endif 

  return 0;
}


/*
Possible output (after around 10 seconds, length of lines may vary slightly):


------------------------------------*
----------------------------------------*
-----------------------------------*
------------------------------*
-------------------------*
--------------------*
---------------*
----------*
-----*
*
*/

