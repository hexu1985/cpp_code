// inserting into a circular_buffer
#include <iostream>
#include "circular_buffer.h"
#include <vector>
#include <string>

int main ()
{
  Hx::circular_buffer<std::string> mycircular_buffer;

  // set some initial values:
  for (int i=1; i<6; i++) mycircular_buffer.push_back(std::string(1, i+'0')); // 1 2 3 4 5

  Hx::circular_buffer<std::string>::iterator it = mycircular_buffer.begin();
  ++it;

  it = mycircular_buffer.insert (it, "10");                  // 1 10 2 3 4 5
  // "it" now points to the newly inserted 10

  mycircular_buffer.insert (it, 2, "20");                     // 1 20 20 10 2 3 4 5
  // "it" no longer valid!

  it = mycircular_buffer.begin()+2;

  std::vector<std::string> myvector (2, "30");
  mycircular_buffer.insert (it,myvector.begin(),myvector.end());
                                                // 1 20 30 30 20 10 2 3 4 5

  std::cout << "mycircular_buffer contains:";
  for (it=mycircular_buffer.begin(); it!=mycircular_buffer.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}

/*
Output:

mycircular_buffer contains: 1 20 30 30 20 10 2 3 4 5
*/

