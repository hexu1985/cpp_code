// enable_if example: two ways of using enable_if
#include <iostream>
#include "type_traits.h"

// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename Hx::enable_if<std::is_integral<T>::value,bool>::type
  is_odd (T i) {return bool(i%2);}

#if __cplusplus >= 201103L
// 2. the second template argument is only valid if T is an integral type:
template < class T,
           class = typename Hx::enable_if<std::is_integral<T>::value>::type>
bool is_even (T i) {return !bool(i%2);}
#else
// 2. the second template argument is only valid if T is an integral type:
template <class T>
bool is_even (T i, 
	typename Hx::enable_if<std::is_integral<T>::value>::type * = 0) 
{return !bool(i%2);}
#endif

int main() {

  short int i = 1;    // code does not compile if type of i is not integral
//  double j = 1.2;

  std::cout << std::boolalpha;
  std::cout << "i is odd: " << is_odd(i) << std::endl;
  std::cout << "i is even: " << is_even(i) << std::endl;
//  std::cout << "j is odd: " << is_odd(j) << std::endl;  // compile error
//  std::cout << "j is even: " << is_even(j) << std::endl; // compile error

  return 0;
}


/*
Output:

i is odd: true
i is even: false
*/
