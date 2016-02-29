// queue::empty
#include "queue.h"        // Dlist_queue
#include <iostream>       // std::cout

int main ()
{
  Dlist_queue<int> myqueue;
  int sum (0);

  for (int i=1;i<=10;i++) myqueue.push(new Dlist_queue<int>::node_type(i));

  while (!myqueue.empty())
  {
	 Dlist_queue<int>::node_type *front = myqueue.pop();
     sum += front->key;
     delete front;
  }

  std::cout << "total: " << sum << '\n';

  return 0;
}
