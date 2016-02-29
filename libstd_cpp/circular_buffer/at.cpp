// circular_buffer::at
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<unsigned> mycircular_buffer (10);   // 10 zero-initialized unsigneds

  // assign some values:
  for (unsigned i=0; i<mycircular_buffer.size(); i++)
    mycircular_buffer.at(i)=i;

  std::cout << "mycircular_buffer contains:";
  for (unsigned i=0; i<mycircular_buffer.size(); i++)
    std::cout << ' ' << mycircular_buffer.at(i);

  std::cout << '\n';

  return 0;
}


/*
Output:

mycircular_buffer contains: 0 1 2 3 4 5 6 7 8 9
*/

