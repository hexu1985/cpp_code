// example for thread::join
#include <iostream>       // std::cout
#include "thread.h"         // std::thread, std::this_thread::sleep_for
#include "chrono.h"
 
void pause_thread(int n) 
{
  Hx::this_thread::sleep_for(Hx::chrono::seconds(n));
  std::cout << "pause of " << n << " seconds ended\n";
}
 
int main() 
{
  std::cout << "Spawning 3 threads...\n";
  Hx::thread t1(pause_thread, 1);
  Hx::thread t2(pause_thread, 2);
  Hx::thread t3(pause_thread, 3);
  std::cout << "Done spawning threads. Now waiting for them to join:\n";
  t1.join();
  t2.join();
  t3.join();
  std::cout << "All threads joined!\n";

  return 0;
}


/*
Output (after 3 seconds):

Spawning 3 threads...
Done spawning threads. Now waiting for them to join:
pause of 1 seconds ended
pause of 2 seconds ended
pause of 3 seconds ended
All threads joined!
*/
