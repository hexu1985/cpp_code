#include <stdlib.h>
#include <iostream>
#include <new>

#include "memory.h"
#include "sputil.h"

static bool no_memory = false;

void *operator new(size_t sz)
{
    void *res;
    bool no_mem = no_memory;
    no_memory = false;
    if (no_mem || (res = malloc(sz)) == 0)
        throw std::bad_alloc();

    return res;
}

void operator delete(void *ptr)
{
    free(ptr);
}

int main()
{
    try
    {
        std::cout << "construct with no memory:\n";
        instrumented *ip = new instrumented;
        no_memory = true;
        Hx::shared_ptr<instrumented> sp0(ip);
    }
    catch(...)
    {
        std::cout << " caught the exception\n";
    }

    try
    {
        std::cout << "reset with no memory:\n";
        Hx::shared_ptr<instrumented> sp1;
        instrumented *ip = new instrumented;
        no_memory = true;
        sp1.reset(ip);
    }
    catch(...)
    {
        std::cout << " caught the exception\n";
    }

    return 0;
}

