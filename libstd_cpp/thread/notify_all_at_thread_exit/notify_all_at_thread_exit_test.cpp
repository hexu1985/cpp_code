// notify_all_at_thread_exit
#include <iostream>           // std::cout
#include "thread.h"             // std::thread
#include "mutex.h"              // std::mutex, std::unique_lock
#include "condition_variable.h" // std::condition_variable

Hx::mutex mtx;
Hx::condition_variable cv;
bool ready = false;

void print_id (int id) {
  Hx::unique_lock<Hx::mutex> lck(mtx);
  while (!ready) cv.wait(lck);
  // ...
  std::cout << "thread " << id << '\n';
}

void go() {
  Hx::unique_lock<Hx::mutex> lck(mtx);
#if __cplusplus >= 201103L
  Hx::notify_all_at_thread_exit(cv, std::move(lck));
#else
  Hx::notify_all_at_thread_exit(cv, lck);
#endif
  ready = true;
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
    threads[i] = Hx::thread(print_id,i);
#else
    threads[i] = new Hx::thread(print_id,i);
#endif
  std::cout << "10 threads ready to race...\n";

  Hx::thread(go).detach();   // go!

#if __cplusplus >= 201103L
  for (auto& th : threads) 
    th.join();
#else
  for (int i=0; i<10; ++i) {
    threads[i]->join();
    delete threads[i];
  }
#endif

  return 0;
} 

/*
Possible output (order of threads may vary):
 




10 threads ready to race...
thread 9
thread 0
thread 7
thread 2
thread 5
thread 4
thread 6
thread 8
thread 3
thread 1
*/
