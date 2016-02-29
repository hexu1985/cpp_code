// unique_ptr swap specialization
#include <iostream>
#include <memory>

int main () {
  std::unique_ptr<int> foo (new int(10));
  std::unique_ptr<int> bar (new int(20));

  swap(foo,bar);

  std::cout << "foo: " << *foo << '\n';
  std::cout << "bar: " << *bar << '\n';

  return 0;
}
