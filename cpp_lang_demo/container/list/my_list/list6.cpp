// list::crbegin/crend
#include <iostream>
#include "list.h"

int main ()
{
  Dlist<int> mylist;
  mylist.insert_tail(new Dlist<int>::node_type(1));
  mylist.insert_tail(new Dlist<int>::node_type(2));
  mylist.insert_tail(new Dlist<int>::node_type(4));
  mylist.insert_tail(new Dlist<int>::node_type(8));
  mylist.insert_tail(new Dlist<int>::node_type(16));

  std::cout << "mylist backwards:";
  for (Dlist<int>::node_type *rit = mylist.tail(); rit != mylist.nil(); 
		  rit = dlist_prev(rit))
    std::cout << ' ' << rit->key;
  std::cout << '\n';

  return 0;
}
