// swap lists
#include <iostream>
#include "list.h"

int main ()
{
  Dlist<int> first;	// three ints with a value of 100
  for (int i = 0; i < 3; i++)
    first.insert_tail(new Dlist<int>::node_type(100));

  Dlist<int> second;  // five ints with a value of 200
  for (int i = 0; i < 5; i++)
    second.insert_tail(new Dlist<int>::node_type(200));

  first.swap(second);

  std::cout << "first contains:";
  for (Dlist<int>::node_type *it=first.head(); it!=first.nil(); it = dlist_next(it))
    std::cout << ' ' << it->key;
  std::cout << '\n';

  std::cout << "second contains:";
  for (Dlist<int>::node_type *it=second.head(); it!=second.nil(); it = dlist_next(it))
    std::cout << ' ' << it->key;
  std::cout << '\n';

  return 0;
}
