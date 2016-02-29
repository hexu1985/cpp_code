// circular_buffer::pop_front
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer;

  mycircular_buffer.push_back (100);
  mycircular_buffer.push_back (200);
  mycircular_buffer.push_back (300);

  std::cout << "Popping out the elements in mycircular_buffer:";
  while (!mycircular_buffer.empty())
  {
    std::cout << ' ' << mycircular_buffer.front();
    mycircular_buffer.pop_front();
  }

  std::cout << "\nThe final size of mycircular_buffer is " << int(mycircular_buffer.size()) << '\n';

  return 0;
}

/*
Output:

Popping out the elements in mycircular_buffer: 100 200 300
The final size of mycircular_buffer is 0
*/
