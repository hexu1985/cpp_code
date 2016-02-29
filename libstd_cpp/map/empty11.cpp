// map::empty
#include <iostream>
#include "map.h"

int main ()
{
  Hx::map<int,int> first;
  Hx::map<int,int> second = {{1,10},{2,20},{3,30}};
  std::cout << "first " << (first.empty() ? "is empty" : "is not empty" ) << std::endl;
  std::cout << "second " << (second.empty() ? "is empty" : "is not empty" ) << std::endl;
  return 0;
}


/*
Output:

first is empty
second is not empty
*/

