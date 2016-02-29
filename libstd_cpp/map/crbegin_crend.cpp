// map::crbegin/crend
#include <iostream>
#include "map.h"

int main ()
{
  Hx::map<char,int> mymap;

  mymap['b'] = 100;
  mymap['a'] = 200;
  mymap['c'] = 300;

  std::cout << "mymap backwards:";
  for (auto rit = mymap.crbegin(); rit != mymap.crend(); ++rit)
    std::cout << " [" << rit->first << ':' << rit->second << ']';
  std::cout << '\n';

  return 0;
}


/*
Output:

mymap backwards: [c:300] [b:100] [a:200]
*/

