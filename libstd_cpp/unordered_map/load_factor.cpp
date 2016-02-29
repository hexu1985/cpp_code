// unordered_map hash table stats
#include <iostream>
#include "unordered_map.h"

int main ()
{
  Hx::unordered_map<int,int> mymap;

  std::cout << "size = " << mymap.size() << std::endl;
  std::cout << "bucket_count = " << mymap.bucket_count() << std::endl;
  std::cout << "load_factor = " << mymap.load_factor() << std::endl;
  std::cout << "max_load_factor = " << mymap.max_load_factor() << std::endl;

  return 0;
}
 

/*
Possible output:


size = 0
bucket_count = 11
load_factor = 0
max_load_factor = 1
*/
 


