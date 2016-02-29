// Auto_ptr example
#include <iostream>
#include "my_auto_ptr.h"

int main () {
  Auto_ptr<int> p1 (new int);
  *p1.get()=10;

  Auto_ptr<int> p2 (p1);

  std::cout << "p2 points to " << *p2 << '\n';
  // (p1 is now null-pointer Auto_ptr)

  return 0;
}
