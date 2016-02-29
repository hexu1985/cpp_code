// map::emplace
#include <iostream>
#include "map.h"

int main ()
{
  Hx::map<char,int> mymap;

  mymap.emplace('x',100);
  mymap.emplace('y',200);
  mymap.emplace('z',100);

  std::cout << "mymap contains:";
  for (auto& x: mymap)
    std::cout << " [" << x.first << ':' << x.second << ']';
  std::cout << '\n';

  return 0;
}

/*
Output:

mymap contains: [x:100] [y:200] [z:100]
*/

