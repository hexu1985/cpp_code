// list::pop_back
#include <iostream>
#include "list.h"

int main ()
{
  Dlist<int> mylist;
  int sum (0);
  mylist.insert_tail(new Dlist<int>::node_type(100));
  mylist.insert_tail(new Dlist<int>::node_type(200));
  mylist.insert_tail(new Dlist<int>::node_type(300));

  while (!mylist.empty())
  {
    sum+=mylist.erase_tail()->key;
  }

  std::cout << "The elements of mylist summed " << sum << '\n';

  return 0;
}
