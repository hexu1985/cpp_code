// constructing lists
#include <iostream>
#include "list.h"

int main ()
{
  // constructors used in the same order as described above:
  Hx::list<int> first;                                // empty list of ints
  Hx::list<int> second (4,100);                       // four ints with value 100
  Hx::list<int> third (second.begin(),second.end());  // iterating through second
  Hx::list<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  Hx::list<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are: ";
  for (Hx::list<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
    std::cout << *it << ' ';

  std::cout << '\n';

  return 0;
}

/*
Output:

The contents of fifth are: 16 2 77 29 
*/

