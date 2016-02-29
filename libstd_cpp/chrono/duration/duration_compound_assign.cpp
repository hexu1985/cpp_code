#include <iostream>
#include "chrono.h"
 
int main()
{
    Hx::chrono::minutes m(11);
    m *= 2;
    m += Hx::chrono::hours(10); // hours implicitly convert to minutes
    std::cout << m.count() << " minutes equals "
              << Hx::chrono::duration_cast<Hx::chrono::hours>(m).count() 
              << " hours and ";
    m %= Hx::chrono::hours(1);
    std::cout << m.count() << " minutes\n";
}

/*
Output:

622 minutes equals 10 hours and 22 minutes
*/
