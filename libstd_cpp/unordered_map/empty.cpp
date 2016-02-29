// unordered_map::empty
#include <iostream>
#include "unordered_map.h"

int main ()
{
  Hx::unordered_map<char,int> mymap;

  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;

  while (!mymap.empty())
  {
    std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
    mymap.erase(mymap.begin());
  }

  return 0;
}
 

/*
Output:


a => 10
b => 20
c => 30
*/


