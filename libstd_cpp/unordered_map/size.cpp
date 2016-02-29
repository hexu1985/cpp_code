// unordered_map::size
#include <iostream>
#include "unordered_map.h"

int main ()
{
  Hx::unordered_map<char,int> mymap;
  mymap['a']=101;
  mymap['b']=202;
  mymap['c']=302;

  std::cout << "mymap.size() is " << mymap.size() << '\n';

  return 0;
}
 

/*
Output:


mymap.size() is 3
*/


