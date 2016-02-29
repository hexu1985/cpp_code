// unique_ptr::swap example
#include <iostream>
#include "my_auto_ptr.h"

int main () {
  Auto_ptr<int> foo (new int(10));
  Auto_ptr<int> bar (new int(20));

  foo.swap(bar);

  std::cout << "foo: " << *foo << '\n';
  std::cout << "bar: " << *bar << '\n';

  return 0;
}
