// list::front
#include <iostream>
#include "list.h"

int main ()
{
  Dlist<int> mylist;

  mylist.insert_tail(new Dlist<int>::node_type(77));
  mylist.insert_tail(new Dlist<int>::node_type(22));

  // now front equals 77, and back 22

  mylist.head()->key -= mylist.tail()->key;

  std::cout << "mylist.front() is now " << mylist.head()->key << '\n';

  return 0;
}
