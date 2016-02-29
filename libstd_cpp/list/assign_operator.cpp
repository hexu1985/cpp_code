// assignment operator with lists
#include <iostream>
#include "list.h"

int main ()
{
  Hx::list<int> first (3);      // list of 3 zero-initialized ints
  Hx::list<int> second (5);     // list of 5 zero-initialized ints

  second = first;
  first = Hx::list<int>();

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  return 0;
}

/*
Both list containers of int elements are initialized to sequences with different sizes. Then, second is assigned to first, so both are now equal and with a size of 3. And then, first is assigned to a newly constructed empty container object, so its size is finally 0. Output:

Size of first: 0
Size of second: 3
*/

