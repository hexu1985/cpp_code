// erasing from list
#include <iostream>
#include "list.h"

int main ()
{
  Dlist<int> mylist;
  Dlist<int>::node_type *it1;
  Dlist<int>::node_type *it2;

  // set some values:
  for (int i=1; i<10; ++i) mylist.insert_tail(new Dlist<int>::node_type(i*10));

                              // 10 20 30 40 50 60 70 80 90
  it1 = it2 = mylist.head();  // ^^
  for (int i = 0; i < 6; i++)
	it2 = dlist_next(it2);    // ^                 ^
  it1 = dlist_next(it1);      //    ^              ^

  it1 = mylist.erase(it1);    // 10 30 40 50 60 70 80 90
                              //    ^           ^

  it2 = mylist.erase(it2);    // 10 30 40 50 60 80 90
                              //    ^           ^

  it1 = dlist_next(it1);      //       ^        ^
  it2 = dlist_prev(it2);      //       ^     ^

  mylist.erase(it1,
		  dlist_prev(it2));   // 10 30 60 80 90
                              //        ^

  std::cout << "mylist contains:";
  for (it1=mylist.head(); it1!=mylist.nil(); it1 = dlist_next(it1))
    std::cout << ' ' << it1->key;
  std::cout << '\n';

  return 0;
}
