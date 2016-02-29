// auto_ptr::release example
#include <iostream>
#include <memory>

int main () {
  std::auto_ptr<int> auto_pointer (new int);
  int * manual_pointer;

  *auto_pointer=10;

  manual_pointer = auto_pointer.release();

  std::cout << "manual_pointer points to " << *manual_pointer << '\n';
  // (auto_pointer is now null-pointer auto_ptr)

  delete manual_pointer; 

  return 0;
}
