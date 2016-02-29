// shared_ptr::operator= example
#include <iostream>
#include "memory.h"

int main () {
  Hx::shared_ptr<int> foo;
  Hx::shared_ptr<int> bar (new int(10));

  foo = bar;                          // copy

  bar = Hx::make_shared<int> (20);   // move

  std::unique_ptr<int> unique (new int(30));
  foo = std::move(unique);            // move from unique_ptr

  std::cout << "*foo: " << *foo << '\n';
  std::cout << "*bar: " << *bar << '\n';

  return 0;
}


/*
Output:

*foo: 30
*bar: 20
*/
