#include <iostream>
#include <ctime>
#include "chrono.h"
 
int fibonacci(int n)
{
    if (n < 3) return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}
 
int main()
{
    Hx::chrono::time_point<Hx::chrono::system_clock> start, end;
    start = Hx::chrono::system_clock::now();
    int result = fibonacci(42);
    end = Hx::chrono::system_clock::now();
 
    int elapsed_seconds = Hx::chrono::duration_cast<Hx::chrono::seconds>
                             (end-start).count();
    std::time_t end_time = Hx::chrono::system_clock::to_time_t(end);
 
    std::cout << "finished computation fibonacci(42) = " << result 
              << " at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds << "s\n";
}

/*
Possible output:

finished computation at Sat Jun 16 20:42:57 2012
elapsed time: 3s
*/
