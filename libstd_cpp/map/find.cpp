// map::find
#include <iostream>
#include "map.h"

int main ()
{
  Hx::map<char,int> mymap;
  Hx::map<char,int>::iterator it;

  mymap['a']=50;
  mymap['b']=100;
  mymap['c']=150;
  mymap['d']=200;

  it=mymap.find('b');
  mymap.erase (it);
  mymap.erase (mymap.find('d'));

  // print content:
  std::cout << "elements in mymap:" << '\n';
  std::cout << "a => " << mymap.find('a')->second << '\n';
  std::cout << "c => " << mymap.find('c')->second << '\n';

  return 0;
}


/*
Output:

elements in mymap:
a => 50
c => 150
*/

