// example of unique_ptr::operator bool
#include <iostream>
#include "my_auto_ptr.h"

int main () {
  Auto_ptr<int> foo;
  Auto_ptr<int> bar (new int(12));

  if (foo) std::cout << "foo points to " << *foo << '\n';
  else std::cout << "foo is empty\n";

  if (bar) std::cout << "bar points to " << *bar << '\n';
  else std::cout << "bar is empty\n";

  return 0;
}
