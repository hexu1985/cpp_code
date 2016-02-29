// circular_buffer::get_allocator
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer;
  int * p;
  unsigned int i;

  // allocate an array with space for 5 elements using circular_buffer's allocator:
  p = mycircular_buffer.get_allocator().allocate(5);

  // construct values in-place on the array:
  for (i=0; i<5; i++) mycircular_buffer.get_allocator().construct(&p[i],i);

  std::cout << "The allocated array contains:";
  for (i=0; i<5; i++) std::cout << ' ' << p[i];
  std::cout << '\n';

  // destroy and deallocate:
  for (i=0; i<5; i++) mycircular_buffer.get_allocator().destroy(&p[i]);
  mycircular_buffer.get_allocator().deallocate(p,5);

  return 0;
}

/*
The example shows an elaborate way to allocate memory for an array of ints using the same allocator used by the circular_buffer object. Output:

The allocated array contains: 0 1 2 3 4
*/
