#include <algorithm>
#include "memory.h"
#include <iostream>
#include <set>

typedef Hx::shared_ptr<int> spi;
typedef std::set<spi> iset;
typedef iset::const_iterator citer;

static void lookup(const iset &data, spi sp)
{
    citer res = std::lower_bound(data.begin(), data.end(), sp);
    std::cout << *sp;
    if (res == data.end() || *res != sp)
        std::cout << " not found\n";
    else
        std::cout << " found\n";
}

int main()
{
    iset data;
    spi sp0(new int(0));
    spi sp1(new int(1));
    spi sp2(new int(2));
    spi sp3(sp1);
    spi sp4(new int(1));

    data.insert(sp0);
    data.insert(sp1);
    data.insert(sp2);
    lookup(data, sp1);
    lookup(data, sp3);
    lookup(data, sp4);

    return 0;
}
