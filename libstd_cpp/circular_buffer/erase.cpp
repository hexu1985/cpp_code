// erasing from circular_buffer
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer;

  // set some values (from 1 to 10)
  for (int i=1; i<=10; i++) mycircular_buffer.push_back(i);

  // erase the 6th element
  mycircular_buffer.erase (mycircular_buffer.begin()+5);

  // erase the first 3 elements:
  mycircular_buffer.erase (mycircular_buffer.begin(),mycircular_buffer.begin()+3);

  std::cout << "mycircular_buffer contains:";
  for (Hx::circular_buffer<int>::iterator it = mycircular_buffer.begin(); it!=mycircular_buffer.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}

/*
Output:

mycircular_buffer contains: 4 5 7 8 9 10
*/
