// unique_ptr::swap example
#include <iostream>
#include <memory>

int main () {
  std::unique_ptr<int> foo (new int(10));
  std::unique_ptr<int> bar (new int(20));

  foo.swap(bar);

  std::cout << "foo: " << *foo << '\n';
  std::cout << "bar: " << *bar << '\n';

  return 0;
}
