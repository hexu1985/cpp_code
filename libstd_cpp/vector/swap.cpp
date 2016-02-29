// swap vectors
#include <iostream>
#include "vector.h"

int main ()
{
  Hx::vector<int> foo (3,100);   // three ints with a value of 100
  Hx::vector<int> bar (5,200);   // five ints with a value of 200

  std::cout << "sizeof (foo): " << sizeof (foo) << '\n';

  foo.swap(bar);

  std::cout << "foo contains:";
  for (unsigned i=0; i<foo.size(); i++)
    std::cout << ' ' << foo[i];
  std::cout << '\n';

  std::cout << "bar contains:";
  for (unsigned i=0; i<bar.size(); i++)
    std::cout << ' ' << bar[i];
  std::cout << '\n';

  return 0;
}


/*
Output:

foo contains: 200 200 200 200 200 
bar contains: 100 100 100 
*/

