// erasing from vector
#include <iostream>
#include "vector.h"
#include <string>
#include <sstream>

std::string to_str(int i)
{
	std::ostringstream os;
	os << i;
	return os.str();
}

int main ()
{
  Hx::vector<std::string> myvector;

  // set some values (from 1 to 10)
  for (int i=1; i<=10; i++) myvector.push_back(to_str(i));

  // erase the 6th element
  myvector.erase (myvector.begin()+5);

  // erase the first 3 elements:
  myvector.erase (myvector.begin(),myvector.begin()+3);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}

/*
Output:

myvector contains: 4 5 7 8 9 10
*/

