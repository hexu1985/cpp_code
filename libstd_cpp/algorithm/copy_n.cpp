// copy_n algorithm example
#include <iostream>     // std::cout
#include "algorithm.h"    // std::copy
#include <vector>       // std::vector

int main () {
  int myints[]={10,20,30,40,50,60,70};
  std::vector<int> myvector;

  myvector.resize(7);   // allocate space for 7 elements

  Hx::copy_n ( myints, 7, myvector.begin() );

  std::cout << "myvector contains:";
  for (std::vector<int>::iterator it = myvector.begin(); it!=myvector.end(); ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

  return 0;
}


/*
Output:

myvector contains: 10 20 30 40 50 60 70
*/
