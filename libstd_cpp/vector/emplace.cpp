// vector::emplace
#include <iostream>
#include "vector.h"

int main ()
{
  Hx::vector<int> myvector = {10,20,30};

  auto it = myvector.emplace ( myvector.begin()+1, 100 );
  myvector.emplace ( it, 200 );
  myvector.emplace ( myvector.end(), 300 );

  std::cout << "myvector contains:";
  for (auto& x: myvector)
    std::cout << ' ' << x;
  std::cout << '\n';

  return 0;
}

/*
Output:

myvector contains: 10 200 100 20 30 300
*/
