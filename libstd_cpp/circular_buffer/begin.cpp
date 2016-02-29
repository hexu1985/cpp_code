// circular_buffer::begin
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer;

  for (int i=1; i<=5; i++) mycircular_buffer.push_back(i);

  std::cout << "mycircular_buffer contains:";

  Hx::circular_buffer<int>::iterator it = mycircular_buffer.begin();

  while (it != mycircular_buffer.end())
    std::cout << ' ' << *it++;

  std::cout << '\n';

  return 0;
}


/*
Output:

mycircular_buffer contains: 1 2 3 4 5
*/

