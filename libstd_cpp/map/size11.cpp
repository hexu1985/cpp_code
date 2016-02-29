// map::size
#include <iostream>
#include <string>
#include "map.h"

int main ()
{
  Hx::map<std::string,double> mymap = {
       {"milk",2.30},
       {"potatoes",1.90},
       {"eggs",0.40}
  };

  std::cout << "mymap.size() is " << mymap.size() << std::endl;

  return 0;
}


/*
Output:

mymap.size() is 3
*/

