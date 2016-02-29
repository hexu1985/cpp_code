// allocate_shared example
#include <iostream>
#include "memory.h"

int main () {
  std::allocator<int> alloc;    // the default allocator for int
  std::default_delete<int> del; // the default deleter for int

  Hx::shared_ptr<int> foo = Hx::allocate_shared<int> (alloc,10);

  auto bar = Hx::allocate_shared<int> (alloc,20);

  auto baz = Hx::allocate_shared<std::pair<int,int>> (alloc,30,40);

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
