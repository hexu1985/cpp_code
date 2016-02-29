// circular_buffer::back
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer;

  mycircular_buffer.push_back(10);

  while (mycircular_buffer.back() != 0)
    mycircular_buffer.push_back ( mycircular_buffer.back() -1 );

  std::cout << "mycircular_buffer contains:";

  for (Hx::circular_buffer<int>::iterator it = mycircular_buffer.begin(); it!=mycircular_buffer.end(); ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

  return 0;
}


/*
Output:

mycircular_buffer contains: 10 9 8 7 6 5 4 3 2 1 0
*/

