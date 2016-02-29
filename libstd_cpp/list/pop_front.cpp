// list::pop_front
#include <iostream>
#include "list.h"

int main ()
{
  Hx::list<int> mylist;
  mylist.push_back (100);
  mylist.push_back (200);
  mylist.push_back (300);

  std::cout << "Popping out the elements in mylist:";
  while (!mylist.empty())
  {
    std::cout << ' ' << mylist.front();
    mylist.pop_front();
  }

  std::cout << "\nFinal size of mylist is " << mylist.size() << '\n';

  return 0;
}

/*
Output:
Popping out the elements in mylist: 100 200 300
Final size of mylist is 0
*/

