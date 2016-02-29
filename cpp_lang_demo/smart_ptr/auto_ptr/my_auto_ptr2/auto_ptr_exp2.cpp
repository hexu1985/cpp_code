// unique_ptr destructor example
#include <iostream>
#include "my_auto_ptr.h"

struct Deleter {
  void operator ()(int *p)
  {
    delete p;
    std::cout << "[deleter called]\n";
  }
} deleter;

int main () {
  Auto_ptr<int, Deleter> foo (new int,deleter);

  std::cout << "foo " << (foo?"is not":"is") << " empty\n";

  return 0;                        // [deleter called]
}
