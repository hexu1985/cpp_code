// list::push_front
#include <iostream>
#include "list.h"

int main ()
{
  Hx::list<int> mylist = {77, 2, 16};
  mylist.push_front (19);
  mylist.push_front (34);

  std::cout << "mylist contains:";
  for (int& x: mylist) std::cout << ' ' << x;
  std::cout << '\n';

  return 0;
}


/*
Output:

mylist contains: 34 19 77 2 16
*/

