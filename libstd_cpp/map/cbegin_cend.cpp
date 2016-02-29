// map::cbegin/cend
#include <iostream>
#include "map.h"

int main ()
{
  Hx::map<char,int> mymap;

  mymap['b'] = 100;
  mymap['a'] = 200;
  mymap['c'] = 300;

  // print content:
  std::cout << "mymap contains:";
  for (auto it = mymap.cbegin(); it != mymap.cend(); ++it)
    std::cout << " [" << (*it).first << ':' << (*it).second << ']';
  std::cout << '\n';

  return 0;
}


/*
Output:

mymap contains: [a:200] [b:100] [c:300]
*/

