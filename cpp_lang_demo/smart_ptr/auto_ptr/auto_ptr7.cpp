// auto_ptr::operator= example
#include <iostream>
#include <memory>

int main () {
  std::auto_ptr<int> p;
  std::auto_ptr<int> p2;

  p = std::auto_ptr<int> (new int);

  *p = 11;

  p2 = p;

  std::cout << "p2 points to " << *p2 << '\n';
  // (p is now null-pointer auto_ptr)

  return 0;
}
