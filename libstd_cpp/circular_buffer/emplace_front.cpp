// circular_buffer::emplace_front
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer = {10,20,30};

  mycircular_buffer.emplace_front (111);
  mycircular_buffer.emplace_front (222);

  std::cout << "mycircular_buffer contains:";
  for (auto& x: mycircular_buffer)
    std::cout << ' ' << x;
  std::cout << '\n';

  return 0;
}

/*
Output:

mycircular_buffer contains: 222 111 10 20 30
*/
