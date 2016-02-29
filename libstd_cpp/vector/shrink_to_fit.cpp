// vector::shrink_to_fit
#include <iostream>
#include "vector.h"

int main ()
{
  Hx::vector<int> myvector (100);
  std::cout << "1. capacity of myvector: " << myvector.capacity() << '\n';

  myvector.resize(10);
  std::cout << "2. capacity of myvector: " << myvector.capacity() << '\n';

  myvector.shrink_to_fit();
  std::cout << "3. capacity of myvector: " << myvector.capacity() << '\n';

  return 0;
}


/*
Possible output:

1. capacity of myvector: 100
2. capacity of myvector: 100
3. capacity of myvector: 10
*/

