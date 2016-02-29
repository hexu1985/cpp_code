// circular_buffer::rbegin/rend
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer (5);  // 5 default-constructed ints

  Hx::circular_buffer<int>::reverse_iterator rit = mycircular_buffer.rbegin();

  int i=0;
  for (rit = mycircular_buffer.rbegin(); rit!= mycircular_buffer.rend(); ++rit)
    *rit = ++i;

  std::cout << "mycircular_buffer contains:";
  for (Hx::circular_buffer<int>::iterator it = mycircular_buffer.begin(); it != mycircular_buffer.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}


/*
Output:

mycircular_buffer contains: 5 4 3 2 1
*/
