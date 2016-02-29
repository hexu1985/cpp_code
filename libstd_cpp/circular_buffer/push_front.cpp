// circular_buffer::push_front
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer (2,100);     // two ints with a value of 100
  mycircular_buffer.push_front (200);
  mycircular_buffer.push_front (300);

  std::cout << "mycircular_buffer contains:";
  for (Hx::circular_buffer<int>::iterator it = mycircular_buffer.begin(); it != mycircular_buffer.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}


/*
Output:

300 200 100 100 
*/

