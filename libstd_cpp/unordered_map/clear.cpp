// unordered_map::clear
#include <iostream>
#include "unordered_map.h"

int main ()
{
  Hx::unordered_map<char,int> mymap;

  mymap['x']=100;
  mymap['y']=200;
  mymap['z']=300;

  std::cout << "mymap contains:\n";
  for (Hx::unordered_map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  mymap.clear();
  mymap['a']=1101;
  mymap['b']=2202;

  std::cout << "mymap contains:\n";
  for (Hx::unordered_map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}
 

/*
Output:


mymap contains:
x => 100
y => 200
z => 300
mymap contains:
a => 1101
b => 2202
*/


