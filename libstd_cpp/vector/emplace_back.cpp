// vector::emplace_back
#include <iostream>
#include "vector.h"

int main ()
{
  Hx::vector<int> myvector = {10,20,30};

  myvector.emplace_back (100);
  myvector.emplace_back (200);

  std::cout << "myvector contains:";
  for (auto& x: myvector)
    std::cout << ' ' << x;
  std::cout << '\n';

  return 0;
}

/*
Output:

myvector contains: 10 20 30 100 200
*/

