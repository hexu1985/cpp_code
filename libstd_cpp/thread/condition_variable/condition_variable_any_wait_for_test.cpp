// condition_variable_any::wait_for example
#include <iostream>           // std::cout
#include "thread.h"             // std::thread
#include "chrono.h"             // std::chrono::seconds
#include "mutex.h"              // std::mutex
#include "condition_variable.h" // std::condition_variable_any, std::cv_status

Hx::condition_variable_any cv;

int value;

void read_value() {
  std::cin >> value;
  cv.notify_one();
}

int main ()
{
  std::cout << "Please, enter an integer (I'll be printing dots): ";
  Hx::thread th (read_value);

  Hx::mutex mtx;
  mtx.lock();
  while (cv.wait_for(mtx,Hx::chrono::seconds(1))==Hx::cv_status::timeout) {
    std::cerr << '.';
  }
  std::cout << "You entered: " << value << '\n';
  mtx.unlock();

  th.join();

  return 0;
}


/*
Possible output:


Please, enter an integer (I'll be priniting dots): .....20
You entered: 20
*/

