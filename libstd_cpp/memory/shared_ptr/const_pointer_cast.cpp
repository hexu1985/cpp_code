// static_pointer_cast example
#include <iostream>
#include "memory.h"

int main () {
  Hx::shared_ptr<int> foo;
  Hx::shared_ptr<const int> bar;

  foo = Hx::make_shared<int>(10);

  bar = Hx::const_pointer_cast<const int>(foo);

  std::cout << "*bar: " << *bar << '\n';
  *foo = 20;
  std::cout << "*bar: " << *bar << '\n';

  return 0;
}


/*
Output:

*bar: 10
*bar: 20
*/

