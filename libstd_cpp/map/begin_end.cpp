// map::begin/end
#include <iostream>
#include "map.h"

int main ()
{
  Hx::map<char,int> mymap;
  Hx::map<char,int>::iterator it;

  mymap['b'] = 100;
  mymap['a'] = 200;
  mymap['c'] = 300;

  // show content:
  for (Hx::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}

/*
Output:
a => 200
b => 100
c => 300
*/

