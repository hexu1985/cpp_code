// unordered_map::cbegin/cend example
#include <iostream>
#include "unordered_map.h"

int main ()
{
  Hx::unordered_map<std::string,std::string> mymap;
  mymap = {{"Australia","Canberra"},{"U.S.","Washington"},{"France","Paris"}};

  std::cout << "mymap contains:";
  for ( auto it = mymap.cbegin(); it != mymap.cend(); ++it )
    std::cout << " " << it->first << ":" << it->second;  // cannot modify *it
  std::cout << std::endl;

  std::cout << "mymap's buckets contain:\n";
  for ( unsigned i = 0; i < mymap.bucket_count(); ++i) {
    std::cout << "bucket #" << i << " contains:";
    for ( auto local_it = mymap.cbegin(i); local_it!= mymap.cend(i); ++local_it )
      std::cout << " " << local_it->first << ":" << local_it->second;
    std::cout << std::endl;
  }

  return 0;
} 


/*
Possible output:

mymap contains: France:Paris Australia:Canberra U.S.:Washington
mymap's buckets contain:
bucket #0 contains:
bucket #1 contains:
bucket #2 contains:
bucket #3 contains:
bucket #4 contains:
bucket #5 contains: France:Paris
bucket #6 contains:
bucket #7 contains: Australia:Canberra
bucket #8 contains: U.S.:Washington
bucket #9 contains:
bucket #10 contains:
*/ 

