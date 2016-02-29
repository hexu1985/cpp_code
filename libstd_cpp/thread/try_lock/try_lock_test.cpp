// std::lock example
#include <iostream>       // std::cout
#include "thread.h"         // std::thread
#include "mutex.h"          // std::mutex, std::try_lock

Hx::mutex foo,bar;

void task_a () {
  foo.lock();
  std::cout << "task a\n";
  bar.lock();
  // ...
  foo.unlock();
  bar.unlock();
}

void task_b () {
  int x = try_lock(bar,foo);
  if (x==-1) {
    std::cout << "task b\n";
    // ...
    bar.unlock();
    foo.unlock();
  }
  else {
    std::cout << "[task b failed: mutex " << (x?"foo":"bar") << " locked]\n";
  }
}

int main ()
{
  Hx::thread th1 (task_a);
  Hx::thread th2 (task_b);

  th1.join();
  th2.join();

  return 0;
}


/*
Possible output:


task a
[task b failed: mutex foo locked]
*/
