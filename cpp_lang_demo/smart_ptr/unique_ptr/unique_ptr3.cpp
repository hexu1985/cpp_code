// unique_ptr::operator= example
#include <iostream>
#include <memory>

int main () {
  std::unique_ptr<int> foo;
  std::unique_ptr<int> bar;

  foo = std::unique_ptr<int>(new int (101));  // rvalue

  bar = std::move(foo);                       // using std::move

  std::cout << "foo: ";
  if (foo) std::cout << *foo << '\n'; else std::cout << "empty\n";

  std::cout << "bar: ";
  if (bar) std::cout << *bar << '\n'; else std::cout << "empty\n";

  return 0;
}
