// unique_ptr::operator*
#include <iostream>
#include <memory>

int main () {
  std::unique_ptr<int> foo (new int);
  std::unique_ptr<int> bar (new int (100));

  *foo = *bar * 2;

  std::cout << "foo: " << *foo << '\n';
  std::cout << "bar: " << *bar << '\n';

  return 0;
}
