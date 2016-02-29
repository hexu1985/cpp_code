// remove from list
#include <iostream>
#include "list.h"

int main ()
{
  int myints[]= {17,89,7,14};
  Dlist<int> mylist;
  for (int i = 0; i < (int) (sizeof(myints)/sizeof(myints[0])); i++)
	  mylist.insert_tail(new Dlist<int>::node_type(myints[i]));

  Dlist<int>::node_type *it = mylist.find(89);
  while (it != mylist.nil()) {
	Dlist<int>::node_type *tmp = dlist_next(it);
	mylist.erase(it);
	it = mylist.find(tmp, 89);
  }

  std::cout << "mylist contains:";
  for (Dlist<int>::node_type *it=mylist.head(); it!=mylist.nil(); it=dlist_next(it))
    std::cout << ' ' << it->key;
  std::cout << '\n';

  return 0;
}
