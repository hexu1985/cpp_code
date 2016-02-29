// list::cbegin/cend
#include <iostream>
#include "list.h"

int main ()
{
  Hx::list<int> mylist = {5,10,15,20};

  std::cout << "mylist contains:";

  for (auto it = mylist.cbegin(); it != mylist.cend(); ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

  return 0;
} 


/*
Output:

mylist contains:  5 10 15 20
*/
 



