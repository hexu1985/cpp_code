// map::key_comp
#include <iostream>
#include "map.h"

int main ()
{
  Hx::map<char,int> mymap;

  Hx::map<char,int>::key_compare mycomp = mymap.key_comp();

  mymap['a']=100;
  mymap['b']=200;
  mymap['c']=300;

  std::cout << "mymap contains:\n";

  char highest = mymap.rbegin()->first;     // key value of last element

  Hx::map<char,int>::iterator it = mymap.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while ( mycomp((*it++).first, highest) );

  std::cout << '\n';

  return 0;
}


/*
Output:

mymap contains:
a => 100
b => 200
c => 300
*/

