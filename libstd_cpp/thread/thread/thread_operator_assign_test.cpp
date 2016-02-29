// example for thread::operator=
#include <iostream>       // std::cout
#include "thread.h"         // std::thread, std::this_thread::sleep_for
#include "chrono.h"         // std::chrono::seconds
 
void pause_thread(int n) 
{
  Hx::this_thread::sleep_for (Hx::chrono::seconds(n));
  std::cout << "pause of " << n << " seconds ended\n";
}

int main() 
{
#if __cplusplus >= 201103L
  Hx::thread threads[5];                         // default-constructed threads
#else
  Hx::thread *threads[5];                         // default-constructed threads
#endif

  std::cout << "Spawning 5 threads...\n";
  for (int i=0; i<5; ++i)
#if __cplusplus >= 201103L
    threads[i] = Hx::thread(pause_thread,i+1);   // move-assign threads
#else
    threads[i] = new Hx::thread(pause_thread,i+1);   // move-assign threads
#endif

  std::cout << "Done spawning threads. Now waiting for them to join:\n";
  for (int i=0; i<5; ++i) {
#if __cplusplus >= 201103L
    threads[i].join();
#else
    threads[i]->join();
	delete threads[i];
#endif
  }

  std::cout << "All threads joined!\n";

  return 0;
}


/*
Output (after 5 seconds):


Spawning 5 threads...
Done spawning threads. Now waiting for them to join:
pause of 1 seconds ended
pause of 2 seconds ended
pause of 3 seconds ended
pause of 4 seconds ended
pause of 5 seconds ended
All threads joined!
*/

