// circular_buffer::cbegin/cend
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer = {10,20,30,40,50};

  std::cout << "mycircular_buffer contains:";

  for (auto it = mycircular_buffer.cbegin(); it != mycircular_buffer.cend(); ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

  return 0;
}


/*
Output:

mycircular_buffer contains: 10 20 30 40 50
*/


