// tuple_size
#include <iostream>     // std::cout
#include <boost/tuple/tuple.hpp>        // boost::tuple, boost::tuples::length

int main ()
{
  typedef boost::tuple<int,char,double> mytuple_type;
  mytuple_type mytuple (10,'a',3.14);

  std::cout << "mytuple has ";
  std::cout << boost::tuples::length<mytuple_type>::value; 
  std::cout << " elements." << '\n';

  return 0;
}
