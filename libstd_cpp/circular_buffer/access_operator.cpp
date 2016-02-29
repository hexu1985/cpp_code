// circular_buffer::operator[] example: reversing order
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer (10);   // 10 zero-initialized elements
  Hx::circular_buffer<int>::size_type sz = mycircular_buffer.size();

  // assign some values:
  for (unsigned i=0; i<sz; i++) mycircular_buffer[i]=i;

  // reverse order of elements using operator[]:
  for (unsigned i=0; i<sz/2; i++)
  {
    int temp;
    temp = mycircular_buffer[sz-1-i];
    mycircular_buffer[sz-1-i]=mycircular_buffer[i];
    mycircular_buffer[i]=temp;
  }

  // print content:
  std::cout << "mycircular_buffer contains:";
  for (unsigned i=0; i<sz; i++)
    std::cout << ' ' << mycircular_buffer[i];
  std::cout << '\n';

  return 0;
}


/*
Output:

mycircular_buffer contains: 9 8 7 6 5 4 3 2 1 0
*/
