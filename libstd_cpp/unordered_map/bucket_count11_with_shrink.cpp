// unordered_map::bucket_count
#include <iostream>
#include <string>
#include "unordered_map.h"

int main ()
{
  Hx::unordered_map<std::string,std::string> mymap = {
            {"house","maison"},
            {"apple","pomme"},
            {"tree","arbre"},
            {"book","livre"},
            {"door","porte"},
            {"grapefruit","pamplemousse"}
  };

  mymap.shrink_to_fit();

  unsigned n = mymap.bucket_count();

  std::cout << "mymap has " << n << " buckets.\n";

  for (unsigned i=0; i<n; ++i) {
    std::cout << "bucket #" << i << " contains: ";
    for (auto it = mymap.begin(i); it!=mymap.end(i); ++it)
      std::cout << "[" << it->first << ":" << it->second << "] ";
    std::cout << "\n";
  }

  return 0;
}


/*
Possible output:

mymap has 7 buckets.
bucket #0 contains: [book:livre] [house:maison] 
bucket #1 contains: 
bucket #2 contains: 
bucket #3 contains: [grapefruit:pamplemousse] [tree:arbre]
bucket #4 contains: 
bucket #5 contains: [apple:pomme]
bucket #6 contains: [door:porte]
*/
