// initializer_list::size
#include <iostream>          // std::cout
#if __cplusplus >= 201103L
#include <initializer_list>  // std::initializer_list
#else
#include "initializer_list.h"  // std::initializer_list
#endif

template<class T> struct simple_container {
  T * data;
  unsigned n;
#if __cplusplus >= 201103L
  simple_container(std::initializer_list<int> args) {
    data = new T [args.size()];
    n=0;
    for (T x : args) {data[n++]=x;}
  }
#else
  simple_container(Hx::initializer_list<int> args) {
    data = new T [args.size()];
    n=0;
    Hx::initializer_list<int>::iterator iter, end; 
    for (iter = args.begin(), end = args.end(); iter != end; ++iter) {
	data[n++]=*iter;
    }
  }
#endif
  T* begin() {return data;}
  T* end() {return data+n;}
};

int main ()
{
#if __cplusplus >= 201103L
  simple_container<int> myobject {10, 20, 30};
#else
  simple_container<int> myobject((int []) {10, 20, 30});
#endif
  std::cout << "myobject contains:";
#if __cplusplus >= 201103L
  for (int x : myobject) std::cout << ' ' << x;
#else
  for (int *beg = myobject.begin(), *end = myobject.end(); beg != end; ++beg)
    std::cout << ' ' << *beg;
#endif
  std::cout << '\n';
  return 0;
}


/*
Output:

myobject contains: 10 20 30
*/

