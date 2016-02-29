// shared_ptr constructor example
#include <iostream>
#include "memory.h"

struct C {int* data;};

int main () {
  Hx::shared_ptr<int> p1;
  Hx::shared_ptr<int> p2 (nullptr);
  Hx::shared_ptr<int> p3 (new int);
  Hx::shared_ptr<int> p4 (new int, std::default_delete<int>());
  Hx::shared_ptr<int> p5 (new int, [](int* p){delete p;}, std::allocator<int>());
  Hx::shared_ptr<int> p6 (p5);
  Hx::shared_ptr<int> p7 (std::move(p6));
  Hx::shared_ptr<int> p8 (std::unique_ptr<int>(new int));
  Hx::shared_ptr<C> obj (new C);
  Hx::shared_ptr<int> p9 (obj, obj->data);

  std::cout << "use_count:\n";
  std::cout << "p1: " << p1.use_count() << '\n';
  std::cout << "p2: " << p2.use_count() << '\n';
  std::cout << "p3: " << p3.use_count() << '\n';
  std::cout << "p4: " << p4.use_count() << '\n';
  std::cout << "p5: " << p5.use_count() << '\n';
  std::cout << "p6: " << p6.use_count() << '\n';
  std::cout << "p7: " << p7.use_count() << '\n';
  std::cout << "p8: " << p8.use_count() << '\n';
  std::cout << "p9: " << p9.use_count() << '\n';
  return 0;
}


/*
Output:

use_count:
p1: 0
p2: 0
p3: 1
p4: 1
p5: 2
p6: 0
p7: 2
p8: 1
p9: 2
*/

