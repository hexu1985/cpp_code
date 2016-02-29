// inserting into a vector
#include <iostream>
#include "vector.h"
#include <string>

int main ()
{
  Hx::vector<std::string> myvector (3,"100");
  Hx::vector<std::string>::iterator it;

  it = myvector.begin();
  it = myvector.insert ( it , "200" );

  myvector.insert (it,2,"300");

  // "it" no longer valid, get a new one:
  it = myvector.begin();

  Hx::vector<std::string> anothervector (2,"400");
  myvector.insert (it+2,anothervector.begin(),anothervector.end());

  std::string myarray [] = { "501","502","503" };
  myvector.insert (myvector.begin(), myarray, myarray+3);

  std::cout << "myvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
 
/*
Output:


myvector contains: 501 502 503 300 300 400 400 200 100 100 100
*/

