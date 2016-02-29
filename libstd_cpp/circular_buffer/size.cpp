// circular_buffer::size
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';

  for (int i=0; i<5; i++) myints.push_back(i);
  std::cout << "1. size: " << myints.size() << '\n';

  myints.insert (myints.begin(),5,100);
  std::cout << "2. size: " << myints.size() << '\n';

  myints.pop_back();
  std::cout << "3. size: " << myints.size() << '\n';

  return 0;
}


/*
Output:

0. size: 0
1. size: 5
2. size: 10
3. size: 9
*/
