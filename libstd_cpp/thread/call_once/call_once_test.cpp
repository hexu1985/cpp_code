// call_once example
#include <iostream>       // std::cout
#include "thread.h"         // std::thread, std::this_thread::sleep_for
#include "chrono.h"         // std::chrono::milliseconds
#include "mutex.h"          // std::call_once, std::once_flag

int winner;
void set_winner (int x) 
{
  winner = x; 
  std::cerr << "in set_winner, sleep 3 seconds\n";
  Hx::this_thread::sleep_for(Hx::chrono::seconds(3));
  std::cerr << "set_winner exit\n";
}

Hx::once_flag winner_flag;

void wait_1000ms (int id) {
  // count to 1000, waiting 1ms between increments:
  for (int i=0; i<1000; ++i)
    Hx::this_thread::sleep_for(Hx::chrono::milliseconds(1));
  // claim to be the winner (only the first such call is executed):
  Hx::call_once (winner_flag,set_winner,id);
  std::cerr << "thread " << id << " exit\n";
}

int main ()
{
#if __cplusplus >= 201103L
  Hx::thread threads[10];
#else
  Hx::thread *threads[10];
#endif

  // spawn 10 threads:
  for (int i=0; i<10; ++i)
#if __cplusplus >= 201103L
    threads[i] = std::move(Hx::thread(wait_1000ms,i+1));
#else
    threads[i] = new Hx::thread(wait_1000ms,i+1);
#endif

  std::cout << "waiting for the first among 10 threads to count 1000 ms...\n";

#if __cplusplus >= 201103L
  for (auto& th : threads) 
    th.join();
#else
  for (int i=0; i<10; ++i) {
    threads[i]->join();
    delete threads[i];
  }
#endif
  std::cout << "winner thread: " << winner << '\n';

  return 0;
} 

/*
Possible output (winner may vary):
 




waiting for the first among 10 threads to count 1000 ms...
winner thread: 2
*/ 

