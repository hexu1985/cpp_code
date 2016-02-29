// vector::cbegin/cend
#include <iostream>
#include "vector.h"

int main ()
{
  Hx::vector<int> myvector = {10,20,30,40,50};

  std::cout << "myvector contains:";

  for (auto it = myvector.cbegin(); it != myvector.cend(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}


/*
Output:

myvector contains: 10 20 30 40 50
*/
