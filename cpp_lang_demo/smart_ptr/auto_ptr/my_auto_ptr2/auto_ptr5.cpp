// Auto_ptr::operator* example
#include <iostream>
#include "my_auto_ptr.h"

int main () {
  Auto_ptr<int> p1 (new int (10));
  Auto_ptr<int> p2 (new int);

  *p2 = *p1 * 2;

  std::cout << "p1 points to: " << *p1 << '\n';
  std::cout << "p2 points to: " << *p2 << '\n';

  return 0;
}
