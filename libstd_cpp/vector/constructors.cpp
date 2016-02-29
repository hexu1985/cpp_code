// constructing vectors
#include <iostream>
#include "vector.h"

int main ()
{
  // constructors used in the same order as described above:
  Hx::vector<int> first;                                // empty vector of ints
  Hx::vector<int> second (4,100);                       // four ints with value 100
  Hx::vector<int> third (second.begin(),second.end());  // iterating through second
  Hx::vector<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  Hx::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are:";
  for (Hx::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
 

/*
Output:


The contents of fifth are: 16 2 77 29 
*/

