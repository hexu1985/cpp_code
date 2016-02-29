// uninitialized_copy_n example
#include <iostream>
#include "memory.h"
#include <string>

int main () {
  std::string numbers[] = {"one","two","three"};

  // get block of uninitialized memory:
  std::pair <std::string*,std::ptrdiff_t> result = Hx::get_temporary_buffer<std::string>(3);

  if (result.second>0) {
    Hx::uninitialized_copy_n ( numbers, result.second, result.first );

    for (int i=0; i<result.second; i++)
      std::cout << result.first[i] << ' ';
    std::cout << '\n';

    Hx::return_temporary_buffer(result.first);
  }

  return 0;
}


/*
Output:

one two three 
*/
