// unique_ptr swap specialization
#include <iostream>
#include "my_auto_ptr.h"

int main () {
  Auto_ptr<int> foo (new int(10));
  Auto_ptr<int> bar (new int(20));

  swap(foo,bar);

  std::cout << "foo: " << *foo << '\n';
  std::cout << "bar: " << *bar << '\n';

  return 0;
}
