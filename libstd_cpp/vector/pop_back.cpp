// vector::pop_back
#include <iostream>
#include "vector.h"

int main ()
{
  Hx::vector<int> myvector;
  int sum (0);
  myvector.push_back (100);
  myvector.push_back (200);
  myvector.push_back (300);

  while (!myvector.empty())
  {
    sum+=myvector.back();
    myvector.pop_back();
  }

  std::cout << "The elements of myvector add up to " << sum << '\n';

  return 0;
}

/*
In this example, the elements are popped out of the vector after they are added up in the sum. Output:

The elements of myvector add up to 600
*/

