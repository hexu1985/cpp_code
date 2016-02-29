// priority_queue::empty
#include <iostream>       // std::cout
#include "priority_queue.h"

int main ()
{
  const int buffer_size = 100;
  int buffer[buffer_size];
  Priority_queue<int> mypq(buffer, buffer_size);
  int sum (0);

  for (int i=1;i<=10;i++) mypq.push(i);

  while (!mypq.empty())
  {
     std::cout << "top: " << mypq.top() << '\n';
     sum += mypq.top();
     mypq.pop();
  }

  std::cout << "total: " << sum << '\n';

  return 0;
}
