// uninitialized_fill_n example
#include <iostream>
#include "memory.h"
#include <string>

int main () {
  // get block of uninitialized memory:
  std::pair <std::string*,std::ptrdiff_t>
    result = Hx::get_temporary_buffer<std::string>(3);

  if (result.second>0) {
    Hx::uninitialized_fill_n ( result.first, result.second, "c++ rocks!" );

    for (int i=0; i<result.second; i++)
      std::cout << result.first[i] << '\n';

    Hx::return_temporary_buffer(result.first);
  }

  return 0;
}


/*
Output:

c++ rocks!
c++ rocks!
c++ rocks!
*/

