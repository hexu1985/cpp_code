// unordered_map::hash_function
#include <iostream>
#include <string>
#include "impl/hash_c_str.h"

int main ()
{
  std::cout << "this: " << hash_c_str("this") << std::endl;
  std::cout << "thin: " << hash_c_str("thin") << std::endl;

  return 0;
}
 

/*
Possible output:


this: 671344778
thin: 3223852919
*/
 
