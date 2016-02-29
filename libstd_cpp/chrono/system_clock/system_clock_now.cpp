#include <iostream>
#include <vector>
#include "chrono.h"
 
int main()
{
#if __cplusplus >= 201103L
    for (unsigned long long size = 1; size < 10000000; size *= 10) {
        auto start = Hx::chrono::system_clock::now();
        std::vector<int> v(size, 42);
        auto end = Hx::chrono::system_clock::now();
 
        auto elapsed = end - start;
        std::cout << size << ": " << elapsed.count() << '\n';
    }
#else
    for (unsigned long long size = 1; size < 10000000; size *= 10) {
        Hx::chrono::system_clock::time_point start = Hx::chrono::system_clock::now();
        std::vector<int> v(size, 42);
        Hx::chrono::system_clock::time_point end = Hx::chrono::system_clock::now();
 
        Hx::chrono::system_clock::duration elapsed = end - start;
        std::cout << size << ": " << elapsed.count() << '\n';
    }
#endif

}

/*
Possible output:

1: 1
10: 2
100: 3
1000: 6
10000: 47
100000: 507
1000000: 4822
*/
