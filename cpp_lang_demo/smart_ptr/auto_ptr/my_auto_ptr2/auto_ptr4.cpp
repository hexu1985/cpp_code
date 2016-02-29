// Auto_ptr::get example
#include <iostream>
#include "my_auto_ptr.h"

int main () {
  Auto_ptr<int> p (new int);

  *p.get() = 100;

  std::cout << "p points to " << *p.get() << '\n';

  return 0;
}
