// Auto_ptr::reset example
#include <iostream>
#include "my_auto_ptr.h"

int main () {
  Auto_ptr<int> p;

  p.reset (new int);
  *p=5;
  std::cout << *p << '\n';

  p.reset (new int);
  *p=10;
  std::cout << *p << '\n';

  return 0;
}
