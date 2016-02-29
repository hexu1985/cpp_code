// map comparisons
#include <iostream>
#include "unordered_map.h"

int main ()
{
  Hx::unordered_map<char,int> foo,bar;
  foo['a']=100;
  foo['b']=200;
  bar['a']=10;
  bar['z']=1000;

  // foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
  if (foo==bar) std::cout << "foo and bar are equal\n";
  if (foo!=bar) std::cout << "foo and bar are not equal\n";

  return 0;
} 


/*
Output:

foo and bar are not equal
*/
 

