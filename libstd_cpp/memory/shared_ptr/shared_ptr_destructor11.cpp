// shared_ptr destructor example
#include <iostream>
#include "memory.h"

int main () {
  auto deleter = [](int*p){
    std::cout << "[deleter called]\n"; delete p;
  };

  Hx::shared_ptr<int> foo (new int,deleter);

  std::cout << "use_count: " << foo.use_count() << '\n';

  return 0;                        // [deleter called]
}


/*
Output:


use_count: 1
[deleter_called]
*/
