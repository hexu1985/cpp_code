// list::begin/end
#include <iostream>
#include "list.h"

int main ()
{
  int myints[] = {75,23,65,42,13};
  Hx::list<int> mylist (myints,myints+5);

  std::cout << "mylist contains:";
  for (Hx::list<int>::iterator it=mylist.begin(); it != mylist.end(); ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

  return 0;
} 


/*
Output:

mylist contains: 75 23 65 42 13
*/


