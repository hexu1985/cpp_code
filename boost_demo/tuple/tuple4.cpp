// make_tuple example
#include <iostream>
#include <boost/functional.hpp>
#include <boost/tuple/tuple.hpp>

int main()
{
  boost::tuple<int, char> 
  first = boost::make_tuple (10,'a');             // tuple < int, char >

  const int a = 0; int b[3];                         // decayed types:
  boost::tuple<int, int *> 
  second = boost::make_tuple (a, (int *)b);               // tuple < int, int* >

  boost::tuple < const int&, const char* >
  third = boost::make_tuple (boost::ref(a),"abc");  // tuple < const int&, const char* >

  std::cout << "third contains: " << boost::get<0>(third);
  std::cout << " and " << boost::get<1>(third);
  std::cout << std::endl;

  return 0;
}

