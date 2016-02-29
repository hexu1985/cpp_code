#include "memory.h"
#include <iomanip>
#include <iostream>

int main()
{
    std::cout << std::boolalpha;
    Hx::shared_ptr<int> sp0(new int(0));
    Hx::shared_ptr<int> sp1(sp0);
    Hx::shared_ptr<int> sp2(new int(2));
    std::cout << "sp0 == sp1: " << (sp0 == sp1) << '\n';
    std::cout << "sp0 == sp2: " << (sp0 == sp2) << '\n';
    std::cout << "sp0 != sp1: " << (sp0 != sp1) << '\n';
    std::cout << "sp0 != sp2: " << (sp0 != sp2) << '\n';

    Hx::shared_ptr<int> sp3;
    Hx::shared_ptr<int> sp4((int *) 0);
    std::cout << "sp3 == sp4: " << (sp3 == sp4) << '\n';
    std::cout << "sp3 != sp4: " << (sp3 != sp4) << '\n';

    return 0;
}
