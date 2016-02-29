#include "memory.h"
#include <iostream>

struct del
{
    void operator ()(void *ptr)
    {
        delete ptr;
    }
};

int main()
{
    Hx::shared_ptr<int> sp0(new int);
    Hx::shared_ptr<int> sp1(new int, del());
    std::cout << Hx::get_deleter<del>(sp0) << '\n';
    std::cout << Hx::get_deleter<del>(sp1) << '\n';

    return 0;
}

