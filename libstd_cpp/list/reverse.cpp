// reversing list
#include <iostream>
#include "list.h"

int main ()
{
  Hx::list<int> mylist;

  for (int i=1; i<10; ++i) mylist.push_back(i);

  mylist.reverse();

  std::cout << "mylist contains:";
  for (Hx::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

  return 0;
}

/*
Output:
mylist contains: 9 8 7 6 5 4 3 2 1
*/
