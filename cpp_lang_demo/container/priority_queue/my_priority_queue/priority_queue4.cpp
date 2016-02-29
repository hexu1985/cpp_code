// priority_queue::top
#include <iostream>       // std::cout
#include "priority_queue.h"

int main ()
{
  const int buffer_size = 100;
  int buffer[buffer_size];
  Priority_queue<int> mypq(buffer, buffer_size);

  mypq.push(10);
  mypq.push(20);
  mypq.push(15);

  std::cout << "mypq.top() is now " << mypq.top() << '\n';

  return 0;
}
