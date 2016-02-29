// unordered_map::bucket
#include <iostream>
#include <string>
#include "unordered_map.h"

int main ()
{
  Hx::unordered_map<std::string,std::string> mymap = {
    {"us","United States"},
    {"uk","United Kingdom"},
    {"fr","France"},
    {"de","Germany"}
  };

  for (auto& x: mymap) {
    std::cout << "Element [" << x.first << ":" << x.second << "]";
    std::cout << " is in bucket #" << mymap.bucket (x.first) << std::endl;
  }

  return 0;
} 


/*
Possible output:

Element [us:United States] is in bucket #1
Element [de:Germany] is in bucket #2
Element [fr:France] is in bucket #2
Element [uk:United Kingdom] is in bucket #4
*/ 

