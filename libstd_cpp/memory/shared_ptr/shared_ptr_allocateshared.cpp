// allocate_shared example
#include <iostream>
#include "memory.h"

int main () {
  std::allocator<int> alloc;    // the default allocator for int

  Hx::shared_ptr<int> foo = Hx::allocate_shared<int> (alloc,10);

  Hx::shared_ptr<std::pair<int, int> > bar = 
    Hx::allocate_shared<std::pair<int,int> >(alloc, std::make_pair(30,40));

  std::cout << "*foo: " << *foo << '\n';
  std::cout << "*bar: " << bar->first << ' ' << bar->second << '\n';

  return 0;
}

/*
Output:

*foo: 10
*bar: 30 40
*/
