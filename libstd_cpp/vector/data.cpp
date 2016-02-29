// vector::data
#include <iostream>
#include "vector.h"

int main ()
{
  Hx::vector<int> myvector (5);

  int* p = myvector.data();

  *p = 10;
  ++p;
  *p = 20;
  p[2] = 100;

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}


/*
Output:

myvector contains: 10 20 0 100 0
*/

