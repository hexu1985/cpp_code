// reversing list
#include <iostream>
#include "list.h"

int main ()
{
  Dlist<int> mylist;

  for (int i=1; i<10; ++i) mylist.insert_tail(new Dlist<int>::node_type(i));

  mylist.reverse();

  std::cout << "mylist contains:";
  for (Dlist<int>::node_type *it=mylist.head(); it!=mylist.nil(); it=dlist_next(it))
    std::cout << ' ' << it->key;

  std::cout << '\n';

  return 0;
}

