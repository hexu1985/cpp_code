// clearing list
#include <iostream>
#include "list.h"

int main ()
{
  Hx::list<int> mylist = { 10, 20, 30 };

  std::cout << "mylist contains:";
  for (int& x: mylist) std::cout << ' ' << x;
  std::cout << '\n';

  mylist.clear();
  mylist.insert( mylist.begin(), {100, 200} );

  std::cout << "mylist contains:";
  for (int& x: mylist) std::cout << ' ' << x;
  std::cout << '\n';

  return 0;
}


/*
Output:

mylist contains: 10 20 30
mylist contains: 100 200
*/
