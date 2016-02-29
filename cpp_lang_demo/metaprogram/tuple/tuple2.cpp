// tuple_size
#include <iostream>     // std::cout
#include <tuple>        // std::tuple, std::tuple_size

int main ()
{
  std::tuple<int,char,double> mytuple (10,'a',3.14);

  std::cout << "mytuple has ";
  std::cout << std::tuple_size<decltype(mytuple)>::value;
  std::cout << " elements." << '\n';

  return 0;
}
