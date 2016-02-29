// auto_ptr::operator* example
#include <iostream>
#include <memory>

int main () {
  std::auto_ptr<int> p1 (new int (10));
  std::auto_ptr<int> p2 (new int);

  *p2 = *p1 * 2;

  std::cout << "p1 points to: " << *p1 << '\n';
  std::cout << "p2 points to: " << *p2 << '\n';

  return 0;
}
