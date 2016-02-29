// list::rbegin/rend
#include <iostream>
#include "list.h"

int main ()
{
  Dlist<int> mylist;
  for (int i=1; i<=5; ++i) mylist.insert_tail(new Dlist<int>::node_type(i));

  std::cout << "mylist backwards:";
  for (Dlist<int>::node_type *rit=mylist.head(); rit!=mylist.nil(); 
		  rit = dlist_next(rit))
    std::cout << ' ' << rit->key;

  std::cout << '\n';

  return 0;
}
