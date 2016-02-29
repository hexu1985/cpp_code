// condition_variable::notify_all
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
  ready = true;
  cv.notify_all();
}

int main ()
{
#if __cplusplus >= 201103L
  Hx::thread threads[10];
#else
  Hx::thread *threads[10];
#endif

  // spawn 10 threads:
#if __cplusplus >= 201103L
  for (int i=0; i<10; ++i)
    threads[i] = Hx::thread(print_id,i);
#else
  for (int i=0; i<10; ++i)
    threads[i] = new Hx::thread(print_id,i);
#endif

  std::cout << "10 threads ready to race...\n";
  go();                       // go!

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
Possible output (thread order may vary):
 




10 threads ready to race...
thread 6
thread 2
thread 5
thread 3
thread 4
thread 1
thread 7
thread 0
thread 9
thread 8
*/ 

