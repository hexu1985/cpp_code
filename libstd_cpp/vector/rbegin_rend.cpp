// vector::rbegin/rend
#include <iostream>
#include "vector.h"

int main ()
{
  Hx::vector<int> myvector (5);  // 5 default-constructed ints

  Hx::vector<int>::reverse_iterator rit = myvector.rbegin();

  int i=0;
  for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
    *rit = ++i;

  std::cout << "myvector contains:";
  for (Hx::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}


/*
Output:

myvector contains: 5 4 3 2 1
*/
