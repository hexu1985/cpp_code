// condition_variable_any::wait (with predicate)
#include <iostream>           // std::cout
#include "thread.h"             // std::thread, std::this_thread::yield
#include "mutex.h"              // std::mutex
#include "condition_variable.h" // std::condition_variable_any

Hx::mutex mtx;
Hx::condition_variable_any cv;

int cargo = 0;
bool shipment_available() {return cargo!=0;}

void consume (int n) {
  for (int i=0; i<n; ++i) {
    mtx.lock();
    cv.wait(mtx,shipment_available);
    // consume:
    std::cout << cargo << '\n';
    cargo=0;
    mtx.unlock();
  }
}

int main ()
{
  Hx::thread consumer_thread (consume,10);

  // produce 10 items when needed:
  for (int i=0; i<10; ++i) {
    while (shipment_available()) Hx::this_thread::yield();
    mtx.lock();
    cargo = i+1;
    cv.notify_one();
    mtx.unlock();
  }

  consumer_thread.join();

  return 0;
}


/*
Output:


1
2
3
4
5
6
7
8
9
10
*/

