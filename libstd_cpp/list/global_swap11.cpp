// swap (forward_list overload)
#include <iostream>
#include "list.h"

int main ()
{
  Hx::list<int> first = {10, 20, 30};
  Hx::list<int> second = {100, 200};
  Hx::list<int>::iterator it;

  Hx::swap(first,second);

  std::cout << "first contains:";
  for (int& x: first) std::cout << ' ' << x;
  std::cout << '\n';

  std::cout << "second contains:";
  for (int& x: second) std::cout << ' ' << x;
  std::cout << '\n';

  return 0;
}


/*
Output:
first contains: 100 200
second contains: 10 20 30
*/


