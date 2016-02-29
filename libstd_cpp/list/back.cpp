// list::back
#include <iostream>
#include "list.h"

int main ()
{
  Hx::list<int> mylist;

  mylist.push_back(10);

  while (mylist.back() != 0)
  {
    mylist.push_back ( mylist.back() -1 );
  }

  std::cout << "mylist contains:";
  for (Hx::list<int>::iterator it=mylist.begin(); it!=mylist.end() ; ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

  return 0;
}

/*
Output:
mylist contains: 10 9 8 7 6 5 4 3 2 1 0
*/

