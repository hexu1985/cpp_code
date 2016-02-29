#include "memory.h"
#include <iostream>

int main()
{
    Hx::shared_ptr<int> sp(new int);
    std::cout << "   get: " << sp.get() << '\n';
    std::cout << "object: " << sp << '\n';

    return 0;
}
