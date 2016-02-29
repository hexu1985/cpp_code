// unique_ptr::reset example
#include <iostream>
#include <memory>

int main () {
  std::unique_ptr<int> up;  // empty

  up.reset (new int);       // takes ownership of pointer
  *up=5;
  std::cout << *up << '\n';

  up.reset (new int);       // deletes managed object, acquires new pointer
  *up=10;
  std::cout << *up << '\n';

  up.reset();               // deletes managed object

  return 0;
}

/*
Output:

5
10
*/
