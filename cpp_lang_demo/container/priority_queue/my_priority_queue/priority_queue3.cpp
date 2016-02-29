// priority_queue::size
#include <iostream>       // std::cout
#include "priority_queue.h"

int main ()
{
  const int buffer_size = 100;
  int buffer[buffer_size];
  Priority_queue<int> myints(buffer, buffer_size);
  std::cout << "0. size: " << myints.size() << '\n';

  for (int i=0; i<5; i++) myints.push(i);
  std::cout << "1. size: " << myints.size() << '\n';

  myints.pop();
  std::cout << "2. size: " << myints.size() << '\n';

  return 0;
}
