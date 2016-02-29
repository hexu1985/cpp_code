#include <iostream>
#include "chrono.h"
 
int main()
{
    Hx::chrono::seconds s1(10);
    Hx::chrono::seconds s2 = -s1;
 
    std::cout << "negated 10 seconds are " << s2.count() << " seconds\n";
}

/*
Output:

negated 10 seconds are -10 seconds
*/
