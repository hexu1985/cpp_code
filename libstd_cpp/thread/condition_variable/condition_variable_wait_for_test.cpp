// condition_variable::wait_for example
#include <iostream>           // std::cout
#include "thread.h"             // std::thread
#include "chrono.h"             // std::chrono::seconds
#include "mutex.h"              // std::mutex
#include "condition_variable.h" // std::condition_variable_any

Hx::condition_variable cv;

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
  Hx::unique_lock<Hx::mutex> lck(mtx);
  while (cv.wait_for(lck,Hx::chrono::seconds(1))==Hx::cv_status::timeout) {
    std::cerr << '.';
  }
  std::cout << "You entered: " << value << '\n';

  th.join();

  return 0;
} 

/*
Possible output:
 




Please, enter an integer (I'll be priniting dots): ....1.0
You entered: 10
*/

