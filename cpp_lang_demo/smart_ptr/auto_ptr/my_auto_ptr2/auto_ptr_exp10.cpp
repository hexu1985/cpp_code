// unique_ptr::operator*
#include <iostream>
#include "my_auto_ptr.h"

int main () {
  Auto_ptr<int> foo (new int);
  Auto_ptr<int> bar (new int (100));

  *foo = *bar * 2;

  std::cout << "foo: " << *foo << '\n';
  std::cout << "bar: " << *bar << '\n';

  return 0;
}
