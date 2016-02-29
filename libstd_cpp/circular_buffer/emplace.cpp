// circular_buffer::emplace
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer = {10,20,30};

  auto it = mycircular_buffer.emplace ( mycircular_buffer.begin()+1, 100 );
  mycircular_buffer.emplace ( it, 200 );
  mycircular_buffer.emplace ( mycircular_buffer.end(), 300 );

  std::cout << "mycircular_buffer contains:";
  for (auto& x: mycircular_buffer)
    std::cout << ' ' << x;
  std::cout << '\n';

  return 0;
}

/*
Output:

mycircular_buffer contains: 10 200 100 20 30 300
*/
