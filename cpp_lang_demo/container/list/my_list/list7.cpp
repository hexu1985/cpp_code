// list::empty
#include <iostream>
#include "list.h"

int main ()
{
  Dlist<int> mylist;
  int sum (0);

  for (int i=1;i<=10;++i) mylist.insert_tail(new Dlist<int>::node_type(i));

  while (!mylist.empty())
  {
     sum += mylist.erase_head()->key;
  }

  std::cout << "total: " << sum << '\n';
  
  return 0;
}
