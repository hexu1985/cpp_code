// tuple constructors
#include <iostream>     // std::cout
#include <utility>      // std::make_pair
#include <tuple>        // std::tuple, std::make_tuple, std::get

int main ()
{
  std::tuple<int,char> first;                             // default
  std::tuple<int,char> second (first);                    // copy
  std::tuple<int,char> third (std::make_tuple(20,'b'));   // move
  std::tuple<long,char> fourth (third);                   // implicit conversion
  std::tuple<int,char> fifth (10,'a');                    // initialization
  std::tuple<int,char> sixth (std::make_pair(30,'c'));    // from pair / move

  std::cout << "sixth contains: " << std::get<0>(sixth);
  std::cout << " and " << std::get<1>(sixth) << '\n';

  return 0;
}
