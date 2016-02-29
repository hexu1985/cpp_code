// list::emplace
#include <iostream>
#include "list.h"

int main ()
{
  Hx::list< std::pair<int,char> > mylist;

  mylist.emplace ( mylist.begin(), 100, 'x' );
  mylist.emplace ( mylist.begin(), 200, 'y' );

  std::cout << "mylist contains:";
  for (auto& x: mylist)
    std::cout << " (" << x.first << "," << x.second << ")";

  std::cout << '\n';
  return 0;
}

/*
Output:
mylist contains: (200,y) (100,x)
*/

