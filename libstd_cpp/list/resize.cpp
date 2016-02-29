// resizing list
#include <iostream>
#include "list.h"

int main ()
{
  Hx::list<int> mylist;

  // set some initial content:
  for (int i=1; i<10; ++i) mylist.push_back(i);

  mylist.resize(5);
  mylist.resize(8,100);
  mylist.resize(12);

  std::cout << "mylist contains:";
  for (Hx::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

  return 0;
}

/*
The code sets a sequence of 9 numbers as an initial content for mylist. It then uses resize first to set the container size to 5, then to extend its size to 8 with values of 100 for its new elements, and finally it extends its size to 12 with their default values (for int elements this is zero). Output:
mylist contains: 1 2 3 4 5 100 100 100 0 0 0 0
*/

