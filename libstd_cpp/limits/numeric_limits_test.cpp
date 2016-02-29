// numeric_limits example
#include <iostream>     // std::cout
#include "limits.h"       // std::numeric_limits

int main () {
  std::cout << std::boolalpha;
  std::cout << "Minimum value for int: " << Hx::numeric_limits<int>::min() << '\n';
  std::cout << "Maximum value for int: " << Hx::numeric_limits<int>::max() << '\n';
  std::cout << "int is signed: " << Hx::numeric_limits<int>::is_signed << '\n';
  std::cout << "Non-sign bits in int: " << Hx::numeric_limits<int>::digits << '\n';
  std::cout << "int has infinity: " << Hx::numeric_limits<int>::has_infinity << '\n';
  return 0;
}
 

/*
Possible output:

Minimum value for int: -2147483648
Maximum value for int: 2147483647
int is signed: true
Non-sign bits in int: 31
int has infinity: false
*/ 

