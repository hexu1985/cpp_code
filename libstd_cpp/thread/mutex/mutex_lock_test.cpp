// mutex example
#include <iostream>       // std::cout
#include <utility>
#include "thread.h"         // std::thread
#include "mutex.h"          // std::mutex

Hx::mutex mtx;           // mutex for critical section

void print_block (int n, char c) {
  // critical section (exclusive access to std::cout signaled by locking mtx):
  mtx.lock();
  for (int i=0; i<n; ++i) { std::cout << c; }
  std::cout << '\n';
  mtx.unlock();
}

int main ()
{
  Hx::thread th1 (print_block,50,'*');
  Hx::thread th2 (print_block,50,'$');

  th1.join();
  th2.join();

  return 0;
}


/*
Possible output (order of lines may vary, but characters are never mixed):


**************************************************
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
*/
