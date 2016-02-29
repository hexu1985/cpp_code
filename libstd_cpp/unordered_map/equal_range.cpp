// unordered_map::equal_range
#include <iostream>
#include "unordered_map.h"

int main ()
{
  Hx::unordered_map<char,int> mymap;

  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;

  std::pair<Hx::unordered_map<char,int>::iterator,Hx::unordered_map<char,int>::iterator> ret;
  ret = mymap.equal_range('b');

  std::cout << "lower bound points to: ";
  std::cout << ret.first->first << " => " << ret.first->second << '\n';

  std::cout << "upper bound points to: ";
  std::cout << ret.second->first << " => " << ret.second->second << '\n';

  return 0;
} 



/*
lower bound points to: 'b' => 20
upper bound points to: 'c' => 30
*/

