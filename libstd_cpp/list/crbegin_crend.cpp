// list::crbegin/crend
#include <iostream>
#include "list.h"

int main ()
{
  Hx::list<int> mylist = {1,2,4,8,16};

  std::cout << "mylist backwards:";
  for (auto rit = mylist.crbegin(); rit != mylist.crend(); ++rit)
    std::cout << ' ' << *rit;
  std::cout << '\n';

  return 0;
} 


/*
Output:

mylist backwards: 16 8 4 2 1
*/ 



