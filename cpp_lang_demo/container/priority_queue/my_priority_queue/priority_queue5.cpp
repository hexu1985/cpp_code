// priority_queue::push/pop
#include <iostream>       // std::cout
#include "priority_queue.h"

int main ()
{
  const int buffer_size = 100;
  int buffer[buffer_size];
  Priority_queue<int> mypq(buffer, buffer_size);

  mypq.push(30);
  mypq.push(100);
  mypq.push(25);
  mypq.push(40);

  std::cout << "Popping out elements...";
  while (!mypq.empty())
  {
     std::cout << ' ' << mypq.top();
     mypq.pop();
  }
  std::cout << '\n';

  return 0;
}
