// circular_buffer::pop_back
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer;
  int sum (0);
  mycircular_buffer.push_back (10);
  mycircular_buffer.push_back (20);
  mycircular_buffer.push_back (30);

  while (!mycircular_buffer.empty())
  {
    sum+=mycircular_buffer.back();
    mycircular_buffer.pop_back();
  }

  std::cout << "The elements of mycircular_buffer add up to " << sum << '\n';

  return 0;
}


/*
In this example, the elements are popped out from the end of the circular_buffer after they are added up in the sum. Output:

The elements of mycircular_buffer summed 60
*/

