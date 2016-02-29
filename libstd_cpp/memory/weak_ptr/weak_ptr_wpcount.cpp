#include "memory.h"
#include <iostream>

typedef Hx::shared_ptr<int> spi;
typedef Hx::weak_ptr<int> wpi;

int main()
{
    wpi wp0;
    std::cout << "empty object: " << wp0.use_count() << '\n';

    spi sp1((int *) 0);
    wpi wp1(sp1);
    std::cout << "null pointer: " << wp1.use_count() << '\n';

    spi sp2(new int);
    wpi wp2(sp2);

    std::cout << "one object: " << wp2.use_count() << '\n';
    {
        spi sp3(sp2);
        std::cout << "two objects: " << wp2.use_count() << '\n';
    }
    std::cout << "one object: " << wp2.use_count() << '\n';
    sp2.reset();
    std::cout << "expired: " << wp2.use_count() << '\n';

    return 0;
}
