// circular_buffer::crbegin/crend
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer = {1,2,3,4,5};

  std::cout << "mycircular_buffer backwards:";
  for (auto rit = mycircular_buffer.crbegin(); rit != mycircular_buffer.crend(); ++rit)
    std::cout << ' ' << *rit;
  std::cout << '\n';

  return 0;
}


/*
Output:

mycircular_buffer backwards: 5 4 3 2 1
*/
