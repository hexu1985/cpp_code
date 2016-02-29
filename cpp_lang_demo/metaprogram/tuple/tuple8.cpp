// tuple's get
#include <iostream>
#include <tuple>

int main ()
{
  std::tuple<int,char> mytuple (10,'a');

  std::get<0>(mytuple) = 20;

  std::cout << "mytuple contains: ";
  std::cout << std::get<0>(mytuple) << " and " << std::get<1>(mytuple);
  std::cout << std::endl;

  return 0;
}
