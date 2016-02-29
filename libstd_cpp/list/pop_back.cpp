// list::pop_back
#include <iostream>
#include "list.h"

int main ()
{
  Hx::list<int> mylist;
  int sum (0);
  mylist.push_back (100);
  mylist.push_back (200);
  mylist.push_back (300);

  while (!mylist.empty())
  {
    sum+=mylist.back();
    mylist.pop_back();
  }

  std::cout << "The elements of mylist summed " << sum << '\n';

  return 0;
}

/*
In this example, the elements are popped out from the end of the list after they are added up in the sum. Output:
The elements of mylist summed 600
*/
