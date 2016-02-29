// circular_buffer::front
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer;

  mycircular_buffer.push_front(77);
  mycircular_buffer.push_back(20);

  mycircular_buffer.front() -= mycircular_buffer.back();

  std::cout << "mycircular_buffer.front() is now " << mycircular_buffer.front() << '\n';

  return 0;
}


/*
Output:

mycircular_buffer.front() is now 57
*/
