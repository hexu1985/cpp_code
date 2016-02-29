// map::get_allocator
#include <iostream>
#include "map.h"

int main ()
{
  int psize;
  Hx::map<char,int> mymap;
  std::pair<const char,int>* p;

  // allocate an array of 5 elements using mymap's allocator:
  p=mymap.get_allocator().allocate(5);

  // assign some values to array
  psize = sizeof(Hx::map<char,int>::value_type)*5;

  std::cout << "The allocated array has a size of " << psize << " bytes.\n";

  mymap.get_allocator().deallocate(p,5);

  return 0;
}

/*
The example shows an elaborate way to allocate memory for an array of pairs using the same allocator used by the container.
A possible output is:

The allocated array has a size of 40 bytes.
*/

