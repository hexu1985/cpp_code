// circular_buffer::shrink_to_fit
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer (100);
  std::cout << "1. size of mycircular_buffer: " << mycircular_buffer.size() << '\n';

  mycircular_buffer.resize(10);
  std::cout << "2. size of mycircular_buffer: " << mycircular_buffer.size() << '\n';

  mycircular_buffer.shrink_to_fit();

  return 0;
}


/*
Output:

1. size of mycircular_buffer: 100
2. size of mycircular_buffer: 10
*/

