#include <iostream>
#include "chrono.h"

int main()
{
    if(Hx::chrono::seconds(2) == Hx::chrono::milliseconds(2000))
        std::cout <<  "2 s == 2000 ms\n";
    else
        std::cout <<  "2 s != 2000 ms\n";
 
    if(Hx::chrono::seconds(61) > Hx::chrono::minutes(1))
        std::cout <<  "61 s > 1 min\n";
    else
        std::cout <<  "61 s <= 1 min\n";
 
}

/*
Output:

2 s == 2000 ms
61 s > 1 min
*/
