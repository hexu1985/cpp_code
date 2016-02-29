// tuple constructors
#include <iostream>     // std::cout
#include <utility>      // boost::make_pair
#include <boost/tuple/tuple.hpp>        // boost::tuple, std::make_tuple, boost::get

int main ()
{
  boost::tuple<int,char> first;                             // default
  boost::tuple<int,char> second (first);                    // copy
  boost::tuple<int,char> third (boost::make_tuple(20,'b'));  
  boost::tuple<long,char> fourth (third);                   // implicit conversion
  boost::tuple<int,char> fifth (10,'a');                    // initialization
  boost::tuple<int,char> sixth;    // from pair
  sixth = std::make_pair(30,'c');

  std::cout << "sixth contains: " << boost::get<0>(sixth);
  std::cout << " and " << boost::get<1>(sixth) << '\n';

  return 0;
}
