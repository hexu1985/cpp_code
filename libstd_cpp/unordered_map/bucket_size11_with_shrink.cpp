// unordered_map::bucket_size
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

  mymap.shrink_to_fit();

  unsigned nbuckets = mymap.bucket_count();

  std::cout << "mymap has " << nbuckets << " buckets:\n";

  for (unsigned i=0; i<nbuckets; ++i) {
    std::cout << "bucket #" << i << " has " << mymap.bucket_size(i) << " elements.\n";
  }

  return 0;
} 


/*
Possible output:

mymap has 5 buckets:
bucket #0 has 0 elements.
bucket #1 has 1 elements.
bucket #2 has 2 elements.
bucket #3 has 0 elements.
bucket #4 has 1 elements.
*/


