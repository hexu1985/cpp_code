// map::at
#include <iostream>
#include <string>
#include "map.h"

int main ()
{
  Hx::map<std::string,int> mymap = {
                { "alpha", 0 },
                { "beta", 0 },
                { "gamma", 0 } };

  mymap.at("alpha") = 10;
  mymap.at("beta") = 20;
  mymap.at("gamma") = 30;

  for (auto& x: mymap) {
    std::cout << x.first << ": " << x.second << '\n';
  }

  return 0;
}


/*
Possible output:

alpha: 10
beta: 20
gamma: 30
*/

