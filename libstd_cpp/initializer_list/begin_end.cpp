// initializer_list::begin/end
#include <iostream>          // std::cout
#include <string>            // std::string
#include <sstream>           // std::stringstream
#if __cplusplus >= 201103L
#include <initializer_list>  // std::initializer_list
#else
#include "initializer_list.h"  // std::initializer_list
#endif

struct myclass {
  std::string str;
#if __cplusplus >= 201103L
  myclass(std::initializer_list<int> args) {
    std::stringstream ss;
    std::initializer_list<int>::iterator it;  // same as: const int* it
    for ( it=args.begin(); it!=args.end(); ++it) ss << ' ' << *it;
    str = ss.str();
  }
#else
  myclass(Hx::initializer_list<int> args) {
    std::stringstream ss;
    Hx::initializer_list<int>::iterator it;  // same as: const int* it
    for ( it=args.begin(); it!=args.end(); ++it) ss << ' ' << *it;
    str = ss.str();
  }
#endif
};

int main ()
{
#if __cplusplus >= 201103L
  myclass myobject {10, 20, 30};
#else
  myclass myobject((int []){10, 20, 30});
#endif
  std::cout << "myobject contains:" << myobject.str << '\n';
  return 0;
}


/*
Output:

myobject contains: 10 20 30
*/


