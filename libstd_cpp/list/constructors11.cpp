// list constructors
#if __cplusplus >= 201103L
#include <iostream>
#include "list.h"

int main ()
{
  // constructors used in the same order as described above:

  Hx::list<int> first;                      // default: empty
  Hx::list<int> second (3,77);              // fill: 3 seventy-sevens
  Hx::list<int> third (second.begin(), second.end()); // range initialization
  Hx::list<int> fourth (third);            // copy constructor
  Hx::list<int> fifth (std::move(fourth));  // move ctor. (fourth wasted)
  Hx::list<int> sixth = {3, 52, 25, 90};    // initializer_list constructor

  std::cout << "first:" ; for (int& x: first)  std::cout << " " << x; std::cout << '\n';
  std::cout << "second:"; for (int& x: second) std::cout << " " << x; std::cout << '\n';
  std::cout << "third:";  for (int& x: third)  std::cout << " " << x; std::cout << '\n';
  std::cout << "fourth:"; for (int& x: fourth) std::cout << " " << x; std::cout << '\n';
  std::cout << "fifth:";  for (int& x: fifth)  std::cout << " " << x; std::cout << '\n';
  std::cout << "sixth:";  for (int& x: sixth)  std::cout << " " << x; std::cout << '\n';

  return 0;
}

/*
Possible output:

list constructor examples:
first:
second: 77 77 77
third: 77 77 77
fourth:
fifth: 77 77 77
sixth: 3 52 25 90
*/
#else
#error "only support by C++11"
#endif
