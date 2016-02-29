// thread::get_id / this_thread::get_id
#include <iostream>       // std::cout
#include "thread.h"         // std::thread, std::thread::id, std::this_thread::get_id
#include "chrono.h"         // std::chrono::seconds
 
Hx::thread::id main_thread_id = Hx::this_thread::get_id();

void is_main_thread() {
  if ( main_thread_id == Hx::this_thread::get_id() )
    std::cout << "This is the main thread.\n";
  else
    std::cout << "This is not the main thread.\n";
}

int main() 
{
  is_main_thread();
  Hx::thread th (is_main_thread);
  th.join();
}


/*
Output:

This is the main thread.
This is not the main thread.
*/

