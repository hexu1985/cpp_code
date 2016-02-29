// vector::empty
#include <iostream>
#include "vector.h"

int main ()
{
  Hx::vector<int> myvector;
  int sum (0);

  for (int i=1;i<=10;i++) myvector.push_back(i);

  while (!myvector.empty())
  {
     sum += myvector.back();
     myvector.pop_back();
  }

  std::cout << "total: " << sum << '\n';

  return 0;
}

/*
The example initializes the content of the vector to a sequence of numbers (form 1 to 10). It then pops the elements one by one until it is empty and calculates their sum.

Output:

total: 55
*/

