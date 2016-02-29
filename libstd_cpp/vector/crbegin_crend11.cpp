// vector::crbegin/crend
#include <iostream>
#include "vector.h"

int main ()
{
  Hx::vector<int> myvector = {1,2,3,4,5};

  std::cout << "myvector backwards:";
  for (auto rit = myvector.crbegin(); rit != myvector.crend(); ++rit)
    std::cout << ' ' << *rit;
  std::cout << '\n';

  return 0;
}


/*
Output:

myvector backwards: 5 4 3 2 1
*/

