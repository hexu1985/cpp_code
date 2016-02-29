// assignment operator with circular_buffers
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> first (3);    // circular_buffer with 3 zero-initialized ints
  Hx::circular_buffer<int> second (5);   // circular_buffer with 5 zero-initialized ints

  second = first;
  first = Hx::circular_buffer<int>();

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  return 0;
}


/*
Output:

Size of first: 0
Size of second: 3
*/
