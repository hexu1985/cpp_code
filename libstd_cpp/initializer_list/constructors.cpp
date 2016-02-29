// initializer_list example
#include <iostream>          // std::cout
#if __cplusplus >= 201103L
#include <initializer_list>  // std::initializer_list
#else
#include "initializer_list.h"  // std::initializer_list
#endif

int main ()
{
#if __cplusplus >= 201103L
  std::initializer_list<int> mylist;
  mylist = { 10, 20, 30 };
#else
  Hx::initializer_list<int> mylist;
  mylist = (int []) { 10, 20, 30 };
#endif
  std::cout << "mylist contains:";
#if __cplusplus >= 201103L
  for (int x: mylist) std::cout << ' ' << x;
#else
  for (Hx::initializer_list<int>::iterator i = mylist.begin(); i != mylist.end(); i++) { int x = *i; std::cout << ' ' << x; }
#endif
  std::cout << '\n';
  return 0;
}


/*
Output:

mylist container: 10 20 30
*/

