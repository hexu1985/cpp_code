// Auto_ptr::operator= example
#include <iostream>
#include "my_auto_ptr.h"

int main () {
  Auto_ptr<int> p;
  Auto_ptr<int> p2;

  p = Auto_ptr<int> (new int);

  *p = 11;

  p2 = p;

  std::cout << "p2 points to " << *p2 << '\n';
  // (p is now null-pointer Auto_ptr)

  return 0;
}
