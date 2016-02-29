#include <iostream>

#include "memory.h"
#include "sputil.h"

struct base0
{
    base0(): i(0) {}

    ~base0()
    {
        std::cout << "destroying base0 at "
            << (void *) this << '\n';
    }

    int i;
};


struct base1
{
    base1(): j(1) {}

    ~base1()
    {
        std::cout << "destroying base1 at "
            << (void *) this << '\n';
    }

    int j;
};

template <class Elem, class Tr>
std::basic_ostream<Elem, Tr> &operator <<(
    std::basic_ostream<Elem, Tr> &str,
    const base1 &b1)
{
    return str << b1.j;
}

struct derived: base0, base1
{
    ~derived()
    {
        std::cout << "destroying derived at "
            << (void *) this << '\n';
    }
};

int main()
{
    Hx::shared_ptr<base1> sp(new derived);
    show("shared_ptr object", sp);

    return 0;
}
