#include <iostream>
#include "ratio.h"
#include "chrono.h"
 
int main()
{
    typedef Hx::chrono::duration<int, Hx::ratio<1, 100000000> > shakes;
    typedef Hx::chrono::duration<int, Hx::centi> jiffies;
    typedef Hx::chrono::duration<float, Hx::ratio<12096,10000> > microfortnights;
    typedef Hx::chrono::duration<float, Hx::ratio<3155,1000> > nanocenturies;
 
    Hx::chrono::seconds sec(1);
 
    std::cout << "1 second is:\n";
 
    std::cout << Hx::chrono::duration_cast<shakes>(sec).count()
              << " shakes\n";
    std::cout << Hx::chrono::duration_cast<jiffies>(sec).count()
              << " jiffies\n";
    std::cout << Hx::chrono::duration_cast<microfortnights>(sec).count()
              << " microfortnights\n";
    std::cout << Hx::chrono::duration_cast<nanocenturies>(sec).count()
              << " nanocenturies\n";
}

/*
Output:

1 second is:
100000000 shakes
100 jiffies
0.82672 microfortnights
0.316957 nanocenturies
*/
