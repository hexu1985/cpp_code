// comparing size, capacity and max_size
#include <iostream>
#include "vector.h"

int main ()
{
  Hx::vector<int> myvector;

  // set some content in the vector:
  for (int i=0; i<100; i++) myvector.push_back(i);

  std::cout << "size: " << myvector.size() << "\n";
  std::cout << "capacity: " << myvector.capacity() << "\n";
  std::cout << "max_size: " << myvector.max_size() << "\n";
  return 0;
}


/*
A possible output for this program could be:

size: 100
capacity: 128
max_size: 1073741823
*/
