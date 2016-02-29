// resizing vector
#include <iostream>
#include "vector.h"

int main ()
{
  Hx::vector<int> myvector;

  // set some initial content:
  for (int i=1;i<10;i++) myvector.push_back(i);

  myvector.resize(5);
  myvector.resize(8,100);
  myvector.resize(12);

  std::cout << "myvector contains:";
  for (size_t i=0;i<myvector.size();i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}


/*
Output:

myvector contains: 1 2 3 4 5 100 100 100 0 0 0 0
*/

