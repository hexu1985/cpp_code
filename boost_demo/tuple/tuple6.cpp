// packing/unpacking tuples
#include <iostream>     // std::cout
#include <boost/tuple/tuple.hpp>        // boost::tuple, boost::make_tuple, boost::tie

int main ()
{
  int myint;
  char mychar;

  boost::tuple<int,float,char> mytuple;

  mytuple = boost::make_tuple (10, 2.6, 'a');          // packing values into tuple

  boost::tie (myint, boost::tuples::ignore, mychar) = mytuple;   // unpacking tuple into variables

  std::cout << "myint contains: " << myint << '\n';
  std::cout << "mychar contains: " << mychar << '\n';

  return 0;
}
