// make_shared example
#include <iostream>
#include "memory.h"

int main () {

  Hx::shared_ptr<int> foo = Hx::make_shared<int> (10);
  // same as:
  Hx::shared_ptr<int> foo2 (new int(10));

  auto bar = Hx::make_shared<int> (20);

  auto baz = Hx::make_shared<std::pair<int,int>> (30,40);

  std::cout << "*foo: " << *foo << '\n';
  std::cout << "*bar: " << *bar << '\n';
  std::cout << "*baz: " << baz->first << ' ' << baz->second << '\n';

  return 0;
}


/*
Output:

*foo: 10
*bar: 20
*baz: 30 40
*/
