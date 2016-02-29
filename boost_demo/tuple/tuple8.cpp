// tuple's get
#include <iostream>
#include <boost/tuple/tuple.hpp>

int main ()
{
  boost::tuple<int,char> mytuple (10,'a');

  boost::get<0>(mytuple) = 20;

  std::cout << "mytuple contains: ";
  std::cout << boost::get<0>(mytuple) << " and " << boost::get<1>(mytuple);
  std::cout << std::endl;

  return 0;
}
