// comparing size, capacity and max_size
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer;

  // set some content in the circular_buffer:
  for (int i=0; i<100; i++) mycircular_buffer.push_back(i);

  std::cout << "size: " << mycircular_buffer.size() << "\n";
  std::cout << "capacity: " << mycircular_buffer.capacity() << "\n";
  std::cout << "max_size: " << mycircular_buffer.max_size() << "\n";
  return 0;
}


/*
A possible output for this program could be:

size: 100
capacity: 128
max_size: 1073741823
*/
