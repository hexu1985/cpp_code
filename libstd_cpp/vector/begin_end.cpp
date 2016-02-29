// vector::begin/end
#include <iostream>
#include "vector.h"

int main ()
{
  Hx::vector<int> myvector;
  for (int i=1; i<=5; i++) myvector.push_back(i);

  std::cout << "myvector contains:";
  for (Hx::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}


/*
Output:

myvector contains: 1 2 3 4 5
*/
