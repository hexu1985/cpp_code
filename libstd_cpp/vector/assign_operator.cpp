
// vector assignment
#include <iostream>
#include "vector.h"

int main ()
{
  Hx::vector<int> foo (3,0);
  Hx::vector<int> bar (5,0);

  bar = foo;
  foo = Hx::vector<int>();

  std::cout << "Size of foo: " << int(foo.size()) << '\n';
  std::cout << "Size of bar: " << int(bar.size()) << '\n';
  return 0;
}
 

/*
Output:


Size of foo: 0
Size of bar: 3
*/ 

