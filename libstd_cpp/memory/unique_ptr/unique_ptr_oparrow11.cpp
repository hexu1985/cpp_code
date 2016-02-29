// unique_ptr::operator->
#include <iostream>
#include <memory>

struct C { int a; int b; };

int main () {
  std::unique_ptr<C> foo (new C);
  std::unique_ptr<C> bar;

  foo->a = 10;
  foo->b = 20;

  bar = std::move(foo);

  if (foo) std::cout << "foo: " << foo->a << ' ' << foo->b << '\n';
  if (bar) std::cout << "bar: " << bar->a << ' ' << bar->b << '\n';

  return 0;
}

/*	
Output:

bar: 10 20
*/
