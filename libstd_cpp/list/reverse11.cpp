// reversing list
#include <iostream>
#include "list.h"

int main ()
{
  Hx::list<int> mylist = {10, 20, 30, 40};

  mylist.reverse();

  std::cout << "mylist contains:";
  for (int& x: mylist) std::cout << ' ' << x;
  std::cout << '\n';

  return 0;
}


/*
Output:

mylist contains: 40 30 20 10
*/

