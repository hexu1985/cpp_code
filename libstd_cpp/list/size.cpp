// list::size
#include <iostream>
#include "list.h"

int main ()
{
  Hx::list<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';

  for (int i=0; i<10; i++) myints.push_back(i);
  std::cout << "1. size: " << myints.size() << '\n';

  myints.insert (myints.begin(),10,100);
  std::cout << "2. size: " << myints.size() << '\n';

  myints.pop_back();
  std::cout << "3. size: " << myints.size() << '\n';

  return 0;
} 


/*
Output:

0. size: 0
1. size: 10
2. size: 20
3. size: 19
*/ 

