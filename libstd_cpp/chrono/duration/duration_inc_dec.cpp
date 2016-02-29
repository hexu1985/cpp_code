#include <iostream>
#include "chrono.h"
 
int main()
{
    Hx::chrono::hours h(1);
    Hx::chrono::minutes m = Hx::chrono::duration_cast<Hx::chrono::minutes>(++h);
    m--;
    std::cout << m.count() << " minutes\n";
}

/*
Output:

119 minutes
*/
