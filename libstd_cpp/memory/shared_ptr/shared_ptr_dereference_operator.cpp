// shared_ptr::operator->
#include <iostream>
#include "memory.h"

struct C { int a; int b; };

int main () {
  Hx::shared_ptr<C> foo;
  Hx::shared_ptr<C> bar (new C);

  foo = bar;

  foo->a = 10;
  bar->b = 20;

  if (foo) std::cout << "foo: " << foo->a << ' ' << foo->b << '\n';
  if (bar) std::cout << "bar: " << bar->a << ' ' << bar->b << '\n';

  return 0;
}

/*	
Output:

foo: 10 20
bar: 10 20
*/
