// circular_buffer::linearize
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer (5);

  int* p = mycircular_buffer.linearize();

  *p = 10;
  ++p;
  *p = 20;
  p[2] = 100;

  std::cout << "mycircular_buffer contains:";
  for (unsigned i=0; i<mycircular_buffer.size(); ++i)
    std::cout << ' ' << mycircular_buffer[i];
  std::cout << '\n';

  return 0;
}


/*
Output:

mycircular_buffer contains: 10 20 0 100 0
*/

