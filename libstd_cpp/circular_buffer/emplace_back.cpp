// circular_buffer::emplace_from
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer = {10,20,30};

  mycircular_buffer.emplace_back (100);
  mycircular_buffer.emplace_back (200);

  std::cout << "mycircular_buffer contains:";
  for (auto& x: mycircular_buffer)
    std::cout << ' ' << x;
  std::cout << '\n';

  return 0;
}

/*
Output:

mycircular_buffer contains: 10 20 30 100 200
*/
