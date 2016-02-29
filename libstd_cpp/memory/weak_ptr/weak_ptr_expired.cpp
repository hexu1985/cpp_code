#include <iomanip>
#include <iostream>
#include "memory.h"
#include "sputil.h"

int main()
{
    std::cout << std::boolalpha;
    Hx::shared_ptr<resource> sp(new resource);
    Hx::weak_ptr<resource> wp(sp);
    std::cout << "points to resource: " << wp.expired() << '\n';
    sp.reset();
    std::cout << "expired: " << wp.expired() << '\n';

    return 0;
}
