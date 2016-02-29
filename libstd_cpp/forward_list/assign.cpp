// forward_list::assign
#include <iostream>
#include "forward_list.h"

int main ()
{
  Hx::forward_list<int> first;
  Hx::forward_list<int> second;

  first.assign (7,100);                      // 7 ints with value 100

  second.assign (first.begin(),first.end()); // a copy of first

  int myints[]={1776,7,4};
  first.assign (myints,myints+3);            // assigning from array

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  return 0;
}

/*
Output:

Size of first: 3
Size of second: 7
*/

