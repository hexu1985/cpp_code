// list::remove_if
#include <iostream>
#include "list.h"

// a predicate implemented as a function:
bool single_digit (const int& value) { return (value<10); }

// a predicate implemented as a class:
struct Is_odd {
  bool operator() (const int& value) { return (value%2)==1; }
};

int main ()
{
  int myints[]= {15,36,7,17,20,39,4,1};
  Dlist<int> mylist;					// 15 36 7 17 20 39 4 1
  for (int i = 0; i < (int) (sizeof(myints)/sizeof(myints[0])); i++)
	  mylist.insert_tail(new Dlist<int>::node_type(myints[i]));

  Dlist<int>::node_type *it = mylist.find_if(single_digit);
  while (it != mylist.nil()) {			// 15 36 17 20 39
	Dlist<int>::node_type *tmp = dlist_next(it);
	mylist.erase(it);
	it = mylist.find_if(tmp, single_digit);
  }
	  
  Is_odd is_odd;
  it = mylist.find_if(is_odd);
  while (it != mylist.nil()) {			// 36 20
	Dlist<int>::node_type *tmp = dlist_next(it);
	mylist.erase(it);
	it = mylist.find_if(tmp, is_odd);
  }

  std::cout << "mylist contains:";
  for (Dlist<int>::node_type *it=mylist.head(); it!=mylist.nil(); it=dlist_next(it))
    std::cout << ' ' << it->key;
  std::cout << '\n';

  return 0;
}
