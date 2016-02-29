// factorial as an integral_constant
#include <iostream>
#include "type_traits.h"

template <unsigned n>
struct factorial: Hx::integral_constant<int,n * factorial<n-1>::value> {};

template <>
struct factorial<0> : Hx::integral_constant<int,1> {};

int main() {
  std::cout << factorial<5>::value << '\n';  // constexpr (no calculations on runtime)
  return 0;
}


/*
Output:

120
*/

