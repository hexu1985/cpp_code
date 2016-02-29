// assignment operator with maps
#include <iostream>
#include "map.h"

int main ()
{
  Hx::map<char,int> first;
  Hx::map<char,int> second;

  first['x']=8;
  first['y']=16;
  first['z']=32;

  second=first;                // second now contains 3 ints
  first=Hx::map<char,int>();  // and first is now empty

  std::cout << "Size of first: " << first.size() << '\n';
  std::cout << "Size of second: " << second.size() << '\n';
  return 0;
}

/*
Output:

Size of first: 0
Size of second: 3
*/

