// mutex::try_lock example
#include <iostream>       // std::cout
#include "thread.h"         // std::thread
#include "mutex.h"          // std::mutex

volatile int counter (0); // non-atomic counter
Hx::mutex mtx;           // locks access to counter

void attempt_10k_increases () {
  for (int i=0; i<10000; ++i) {
    if (mtx.try_lock()) {   // only increase if currently not locked:
      ++counter;
      mtx.unlock();
    }
  }
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
    threads[i] = Hx::thread(attempt_10k_increases);
#else
    threads[i] = new Hx::thread(attempt_10k_increases);
#endif 

#if __cplusplus >= 201103L
  for (auto& th : threads) th.join();
#else
  for (int i=0; i<10; ++i) {
    threads[i]->join();
    delete threads[i];
  }
#endif 
  std::cout << counter << " successful increases of the counter.\n";

  return 0;
}


/*
Possible output (any count between 1 and 100000 possible):


80957 successful increases of the counter.
*/
