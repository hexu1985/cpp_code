// list::back
#include <iostream>
#include "list.h"

int main ()
{
  Dlist<int> mylist;

  mylist.insert_tail(new Dlist<int>::node_type(10));

  while (mylist.tail()->key != 0)
  {
    mylist.insert_tail(new Dlist<int>::node_type(mylist.tail()->key -1));
  }

  std::cout << "mylist contains:";
  for (Dlist<int>::node_type *it=mylist.head(); it!=mylist.nil() ;
		  it = dlist_next(it))
    std::cout << ' ' << it->key;

  std::cout << '\n';

  return 0;
}
