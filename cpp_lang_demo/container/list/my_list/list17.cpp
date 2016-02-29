// list::push_back
#include <iostream>
#include "list.h"

int main ()
{
  Dlist<int> mylist;
  int myint;

  std::cout << "Please enter some integers (enter 0 to end):\n";

  do {
    std::cin >> myint;
    mylist.insert_tail(new Dlist<int>::node_type(myint));
  } while (myint);

  std::cout << "mylist stores " << mylist.size() << " numbers.\n";

  return 0;
}
