// auto_ptr::reset example
#include <iostream>
#include <memory>

int main () {
  std::auto_ptr<int> p;

  p.reset (new int);
  *p=5;
  std::cout << *p << '\n';

  p.reset (new int);
  *p=10;
  std::cout << *p << '\n';

  return 0;
}
