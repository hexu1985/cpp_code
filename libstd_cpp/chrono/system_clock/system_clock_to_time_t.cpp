// system_clock::to_time_t
#include <iostream>
#include <ctime>
#include "ratio.h"
#include "chrono.h"

int main ()
{
  using namespace Hx::chrono;

  duration<int,Hx::ratio<60*60*24> > one_day (1);

  system_clock::time_point today = system_clock::now();
#if __cplusplus >= 201103L
  system_clock::time_point tomorrow = today + one_day;
#else
  system_clock::time_point tomorrow = today + 
    duration_cast<system_clock::duration>(one_day);
#endif

  time_t tt;

  tt = system_clock::to_time_t ( today );
  std::cout << "today is: " << ctime(&tt);

  tt = system_clock::to_time_t ( tomorrow );
  std::cout << "tomorrow will be: " << ctime(&tt);

  return 0;
}


/*
Possible output:

today is: Wed May 30 12:25:03 2012
tomorrow will be: Thu May 31 12:25:03 2012
*/
