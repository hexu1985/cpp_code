#include <iostream>
#include <ostream>

#include "memory.h"
#include "sputil.h"

resource *get_resource(int i)
{
    resource *res = new resource(i);
    std::cout << "created resource with value "
        << *res << '\n';
    return res;
}

void destroy_resource(resource *res)
{
    std::cout << "destroying resource with value "
        << *res << '\n';
    delete res;
}

int main()
{
    Hx::shared_ptr<resource> sp(get_resource(3),
        destroy_resource);

    std::cout << "In main, resource has value "
        << *sp << '\n';

    return 0;
}

