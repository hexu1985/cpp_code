// this_thread::sleep_for example
#include <iostream>       // std::cout
#include <iomanip>        // std::put_time
#include "thread.h"         // std::this_thread::sleep_until
#include "chrono.h"         // std::chrono::system_clock
#include <ctime>          // std::time_t, std::tm, std::localtime, std::mktime

int main() 
{
  using Hx::chrono::system_clock;
  std::time_t tt = system_clock::to_time_t (system_clock::now());

  struct std::tm * ptm = std::localtime(&tt);
//#if __cplusplus >= 201103L
 // std::cout << "Current time: " << std::put_time(ptm,"%X") << '\n';
//#else
  char buffer[16] = "";
  strftime(buffer, sizeof (buffer), "%X", ptm);
  std::cout << "Current time: " << buffer << '\n';
//#endif

  std::cout << "Waiting for the next minute to begin...\n";
  ++ptm->tm_min; ptm->tm_sec=0;
  Hx::this_thread::sleep_until (system_clock::from_time_t (mktime(ptm)));

//#if __cplusplus >= 201103L
 // std::cout << std::put_time(ptm,"%X") << " reached!\n";
//#else
  std::cout << buffer << " reached!\n";
//#endif

  return 0;
}


/*
Output (after an avg. of 30 seconds):

Current time: 11:52:36
Waiting for the next minute to begin...
11:53:00 reached!
*/

