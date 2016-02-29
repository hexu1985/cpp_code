// clearing circular_buffers
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  unsigned int i;
  Hx::circular_buffer<int> mycircular_buffer;
  mycircular_buffer.push_back (100);
  mycircular_buffer.push_back (200);
  mycircular_buffer.push_back (300);

  std::cout << "mycircular_buffer contains:";
  for (Hx::circular_buffer<int>::iterator it = mycircular_buffer.begin(); it!=mycircular_buffer.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  mycircular_buffer.clear();
  mycircular_buffer.push_back (1101);
  mycircular_buffer.push_back (2202);

  std::cout << "mycircular_buffer contains:";
  for (Hx::circular_buffer<int>::iterator it = mycircular_buffer.begin(); it!=mycircular_buffer.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}


/*
Output:

mycircular_buffer contains: 100 200 300
mycircular_buffer contains: 1101 2202
*/

