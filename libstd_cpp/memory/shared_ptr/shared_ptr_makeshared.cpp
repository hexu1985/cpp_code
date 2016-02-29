// make_shared example
#include <iostream>
#include "memory.h"

int main () {

  Hx::shared_ptr<int> foo = Hx::make_shared<int> (10);
  // same as:
  Hx::shared_ptr<int> foo2 (new int(10));

  Hx::shared_ptr<std::pair<int, int> > bar = 
    Hx::make_shared<std::pair<int,int> >(std::make_pair(30,40));

  std::cout << "*foo: " << *foo << '\n';
  std::cout << "*bar: " << bar->first << ' ' << bar->second << '\n';

  return 0;
}


/*
Output:

*foo: 10
*bar: 30 40
*/
