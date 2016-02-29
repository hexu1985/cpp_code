// duration::min/max
#include <iostream>
#include "chrono.h"

int main ()
{
  std::cout << "system_clock durations can represent:\n";
  std::cout << "min: " << Hx::chrono::system_clock::duration::min().count() << "\n";
  std::cout << "max: " << Hx::chrono::system_clock::duration::max().count() << "\n";
  return 0;
}

/*
Possible output:

system_clock durations can represent:
min: -9223372036854775808
max: 9223372036854775807
*/

