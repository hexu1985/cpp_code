// splicing lists
#include <iostream>
#include "list.h"

int main ()
{
  Dlist<int> mylist1, mylist2;
  Dlist<int>::node_type *it;

  // set some initial values:
  for (int i=1; i<=4; ++i)
     mylist1.insert_tail(new Dlist<int>::node_type(i));      
  // mylist1: 1 2 3 4

  for (int i=1; i<=3; ++i)
     mylist2.insert_tail(new Dlist<int>::node_type(i*10));
  // mylist2: 10 20 30

  it = mylist1.head();
  it = dlist_next(it);          // points to 2

  mylist1.splice (it, mylist2); // mylist1: 1 10 20 30 2 3 4
                                // mylist2 (empty)
                                // "it" still points to 2 (the 5th element)
                                          
  mylist2.splice (mylist2.head(),mylist1, it);
                                // mylist1: 1 10 20 30 3 4
                                // mylist2: 2
                                // "it" is now invalid.
  it = mylist1.head();
  for (int i = 0; i < 3; i++)
	  it = dlist_next(it);		// "it" points now to 30

  mylist1.splice ( mylist1.head(), mylist1, it, mylist1.tail());
                                // mylist1: 30 3 4 1 10 20

  std::cout << "mylist1 contains:";
  for (it=mylist1.head(); it!=mylist1.nil(); it = dlist_next(it))
    std::cout << ' ' << it->key;
  std::cout << '\n';

  std::cout << "mylist2 contains:";
  for (it=mylist2.head(); it!=mylist2.nil(); it = dlist_next(it))
    std::cout << ' ' << it->key;
  std::cout << '\n';

  return 0;
}
