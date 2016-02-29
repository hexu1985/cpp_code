// circular_buffer::empty
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer;
  int sum (0);

  for (int i=1;i<=10;i++) mycircular_buffer.push_back(i);

  while (!mycircular_buffer.empty())
  {
     sum += mycircular_buffer.front();
     mycircular_buffer.pop_front();
  }

  std::cout << "total: " << sum << '\n';

  return 0;
}

/*
The example initializes the content of the container to a sequence of numbers (form 1 to 10). It then pops the elements one by one until the container is empty and calculates their sum.

Output:

total: 55
*/
