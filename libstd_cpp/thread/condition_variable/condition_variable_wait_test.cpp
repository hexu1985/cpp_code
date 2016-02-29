// condition_variable::wait (with predicate)
#include <iostream>           // std::cout
#include "thread.h"             // std::thread
#include "mutex.h"              // std::mutex
#include "condition_variable.h" // std::condition_variable_any

Hx::mutex mtx;
Hx::condition_variable cv;

int cargo = 0;
bool shipment_available() {return cargo!=0;}

void consume (int n) {
  for (int i=0; i<n; ++i) {
    Hx::unique_lock<Hx::mutex> lck(mtx);
    cv.wait(lck,shipment_available);
    // consume:
    std::cout << cargo << '\n';
    cargo=0;
  }
}

int main ()
{
  Hx::thread consumer_thread (consume,10);

  // produce 10 items when needed:
  for (int i=0; i<10; ++i) {
    while (shipment_available()) Hx::this_thread::yield();
    Hx::unique_lock<Hx::mutex> lck(mtx);
    cargo = i+1;
    cv.notify_one();
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

