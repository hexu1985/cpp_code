// this_thread::yield example
#include <iostream>       // std::cout
#include "thread.h"         // std::thread, std::this_thread::yield
#if __cplusplus >= 201103L
#include <atomic>         // std::atomic
#else
#include <csignal>
#endif

#if __cplusplus >= 201103L
std::atomic<bool> ready (false);
#else
sig_atomic_t ready = false;
#endif

void count1m(int id) {
  while (!ready) {             // wait until main() sets ready...
    Hx::this_thread::yield();
  }
  for (volatile int i=0; i<1000000; ++i) {}
  std::cout << id;
}

int main ()
{
#if __cplusplus >= 201103L
  Hx::thread threads[10];
#else
  Hx::thread *threads[10];
#endif

  std::cout << "race of 10 threads that count to 1 million:\n";
#if __cplusplus >= 201103L
  for (int i=0; i<10; ++i) threads[i]=Hx::thread(count1m,i);
#else
  for (int i=0; i<10; ++i) threads[i]=new Hx::thread(count1m,i);
#endif
  ready = true;               // go!
#if __cplusplus >= 201103L
  for (auto& th : threads) th.join();
#else
  for (int i=0; i<10; ++i) {
    threads[i]->join();
    delete threads[i];
  }
#endif
  std::cout << '\n';

  return 0;
}


/*
Possible output (last line may vary):

race of 10 threads that count to 1 million...
6189370542
*/

