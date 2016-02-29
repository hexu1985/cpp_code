// unique_ptr::get vs unique_ptr::release
#include <iostream>
#include <memory>

int main () {
                                           // foo   bar    p
                                           // ---   ---   ---
  std::unique_ptr<int> foo;                // null
  std::unique_ptr<int> bar;                // null  null
  int* p = nullptr;                        // null  null  null

  foo = std::unique_ptr<int>(new int(10)); // (10)  null  null
  bar = std::move(foo);                    // null  (10)  null
  p = bar.get();                           // null  (10)  (10)
  *p = 20;                                 // null  (20)  (20)
  p = nullptr;                             // null  (20)  null

  foo = std::unique_ptr<int>(new int(30)); // (30)  (20)  null
  p = foo.release();                       // null  (20)  (30)
  *p = 40;                                 // null  (20)  (40)

  std::cout << "foo: ";
  if (foo) std::cout << *foo << '\n'; else std::cout << "(null)\n";

  std::cout << "bar: ";
  if (bar) std::cout << *bar << '\n'; else std::cout << "(null)\n";

  std::cout << "p: ";
  if (p) std::cout << *p << '\n'; else std::cout << "(null)\n";
  std::cout << '\n';

  delete p;   // the program is now responsible of deleting the object pointed to by p
              // bar deletes its managed object automatically

  return 0;
}
