// this_thread::sleep_for example
#include <iostream>       // std::cout
#include "thread.h"         // std::this_thread::sleep_for
#include "chrono.h"         // std::chrono::seconds
 
int main() 
{
  std::cout << "countdown:\n";
  Hx::chrono::seconds one_second(1);
  for (int i=10; i>0; --i) {
    std::cout << i << '\n';
    Hx::this_thread::sleep_for (one_second);
  }
  std::cout << "Lift off!\n";

  return 0;
}


/*
Output (after 10 seconds):

countdown:
10
9
8
7
6
5
4
3
2
1
Lift off!
*/

