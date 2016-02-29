// unordered_map::erase
#include <iostream>
#include <string>
#include "unordered_map.h"

int main ()
{
  Hx::unordered_map<std::string,std::string> mymap;

  // populating container:
  mymap["U.S."] = "Washington";
  mymap["U.K."] = "London";
  mymap["France"] = "Paris";
  mymap["Russia"] = "Moscow";
  mymap["China"] = "Beijing";
  mymap["Germany"] = "Berlin";
  mymap["Japan"] = "Tokyo";

  // erase examples:
  mymap.erase ( mymap.begin() );      // erasing by iterator
  mymap.erase ("France");             // erasing by key
  mymap.erase ( mymap.find("China"), mymap.end() ); // erasing by range

  // show content:
  for ( auto& x: mymap )
    std::cout << x.first << ": " << x.second << std::endl;

  return 0;
}

/*
Possible output:

Russia: Moscow
Japan: Tokyo
U.K.: London
*/

