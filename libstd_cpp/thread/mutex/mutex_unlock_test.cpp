// mutex::lock/unlock
#include <iostream>       // std::cout
#include "thread.h"         // std::thread
#include "mutex.h"          // std::mutex

Hx::mutex mtx;           // mutex for critical section

void print_thread_id (int id) {
  // critical section (exclusive access to std::cout signaled by locking mtx):
  mtx.lock();
  std::cout << "thread #" << id << '\n';
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
    threads[i] = Hx::thread(print_thread_id, i+1);
#else
    threads[i] = new Hx::thread(print_thread_id, i+1);
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
Possible output (order of lines may vary, but they are never intermingled):

thread #1
thread #2
thread #3
thread #4
thread #5
thread #6
thread #7
thread #8
thread #9
thread #10
*/
