// constructing circular_buffers
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  unsigned int i;

  // constructors used in the same order as described above:
  Hx::circular_buffer<int> first;                                // empty circular_buffer of ints
  Hx::circular_buffer<int> second (4,100);                       // four ints with value 100
  Hx::circular_buffer<int> third (second.begin(),second.end());  // iterating through second
  Hx::circular_buffer<int> fourth (third);                       // a copy of third

  // the iterator constructor can be used to copy arrays:
  int myints[] = {16,2,77,29};
  Hx::circular_buffer<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are:";
  for (Hx::circular_buffer<int>::iterator it = fifth.begin(); it!=fifth.end(); ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

  return 0;
}

/*
Output:

The contents of fifth are: 16 2 77 29 
*/

