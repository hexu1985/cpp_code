// list::rbegin/rend
#include <iostream>
#include "list.h"

int main ()
{
  Hx::list<int> mylist;
  for (int i=1; i<=5; ++i) mylist.push_back(i);

  std::cout << "mylist backwards:";
  for (Hx::list<int>::reverse_iterator rit=mylist.rbegin(); rit!=mylist.rend(); ++rit)
    std::cout << ' ' << *rit;

  std::cout << '\n';

  return 0;
} 


/*
Output:

mylist backwards: 5 4 3 2 1
*/
 



