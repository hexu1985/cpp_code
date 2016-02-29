// tuple_element
#include <iostream>     // std::cout
#include <boost/tuple/tuple.hpp>        // boost::tuple, boost::make_tuple, boost::tuples::element, boost::get

int main ()
{
  typedef boost::tuple<int, char> mytuple_type;
  mytuple_type mytuple = boost::make_tuple (10,'a');

  boost::tuples::element<0,mytuple_type>::type first = boost::get<0>(mytuple);
  boost::tuples::element<1,mytuple_type>::type second = boost::get<1>(mytuple);

  std::cout << "mytuple contains: " << first << " and " << second << '\n';

  return 0;
}
