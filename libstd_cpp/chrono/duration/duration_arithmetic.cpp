#include <iostream>
#include "chrono.h"

int main()
{
    // simple arithmetic
#if __cplusplus >= 201103L
    Hx::chrono::seconds s = Hx::chrono::hours(1) 
                             + 2*Hx::chrono::minutes(10)
                             + Hx::chrono::seconds(70)/10;
#else
    Hx::chrono::seconds s = 
        Hx::chrono::duration_cast<Hx::chrono::seconds>
	    (Hx::chrono::hours(1)) + 
        Hx::chrono::duration_cast<Hx::chrono::seconds>
            (2*Hx::chrono::minutes(10)) + 
        Hx::chrono::duration_cast<Hx::chrono::seconds>
	    (Hx::chrono::seconds(70)/10);
#endif
 
    std::cout << "1 hour + 2*10 min + 70/10 sec = " << s.count() << " seconds\n";
 
    // difference between dividing a duration by a number
    // and dividing a duration by another duration
#if __cplusplus >= 201103L
    std::cout << "Dividing that by 2 minutes gives "
              << s / Hx::chrono::minutes(2) << '\n';
#else
    std::cout << "Dividing that by 2 minutes gives "
              << s / Hx::chrono::duration_cast<Hx::chrono::seconds>(Hx::chrono::minutes(2)) << '\n';
#endif
        
    std::cout << "Dividing that by 2 gives "
              << (s / 2).count() << " seconds\n";
 
   // the remainder operator is useful in determining where in a time
   // frame is this particular duration, e.g. to break it down into hours,
   // minutes, and seconds:
#if __cplusplus >= 201103L
   std::cout << s.count() << " seconds is "
             << Hx::chrono::duration_cast<Hx::chrono::hours>(
                    s
                ).count() << " hours, "
             << Hx::chrono::duration_cast<Hx::chrono::minutes>(
                    s % Hx::chrono::hours(1)
                ).count() << " minutes, "
             << Hx::chrono::duration_cast<Hx::chrono::seconds>(
                    s % Hx::chrono::minutes(1)
                ).count() << " seconds\n";
#else
   std::cout << s.count() << " seconds is "
             << Hx::chrono::duration_cast<Hx::chrono::hours>(
                    s
                ).count() << " hours, "
             << Hx::chrono::duration_cast<Hx::chrono::minutes>(
                    s % Hx::chrono::duration_cast<Hx::chrono::seconds>
                       (Hx::chrono::hours(1))
                ).count() << " minutes, "
             << Hx::chrono::duration_cast<Hx::chrono::seconds>(
                    s % Hx::chrono::duration_cast<Hx::chrono::seconds>
                       (Hx::chrono::minutes(1))
                ).count() << " seconds\n";
#endif
}

/*
Output:

1 hour + 2*10 min + 70/10 sec = 4807 seconds
Dividing that by 2 minutes gives 40
Dividing that by 2 gives 2403 seconds
4807 seconds is 1 hours, 20 minutes, 7 seconds
*/
