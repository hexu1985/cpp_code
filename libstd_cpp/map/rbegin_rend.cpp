// map::rbegin/rend
#include <iostream>
#include "map.h"

int main ()
{
  Hx::map<char,int> mymap;

  mymap['x'] = 100;
  mymap['y'] = 200;
  mymap['z'] = 300;

  // show content:
  Hx::map<char,int>::reverse_iterator rit;
  for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
    std::cout << rit->first << " => " << rit->second << '\n';

  return 0;
}


/*
Output:

z => 300
y => 200
x => 100
*/

