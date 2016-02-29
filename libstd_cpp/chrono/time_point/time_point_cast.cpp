// time_point_cast
#include <iostream>
#include "ratio.h"
#include "chrono.h"

int main ()
{
  using namespace Hx::chrono;

  typedef duration<int,Hx::ratio<60*60*24> > days_type;

  time_point<system_clock,days_type> today = time_point_cast<days_type>(system_clock::now());

  std::cout << today.time_since_epoch().count() << " days since epoch" << std::endl;

  return 0;
}


/*
Possible output:

15490 days since epoch
*/

