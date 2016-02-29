#include "memory.h"
#include "sputil.h"

struct base0
{
    base0(int i0): i(i0) {}
    virtual ~base0() {}
    int i;
};

template <class Elem, class Tr>
std::basic_ostream<Elem, Tr> &operator <<(
    std::basic_ostream<Elem, Tr> &str,
    const base0 &b0)
{
    return str << b0.i;
}

struct base1
{
    base1(int j0): j(j0) {}
    virtual ~base1() {}
    int j;
};

template <class Elem, class Tr>
std::basic_ostream<Elem, Tr> &operator <<(
    std::basic_ostream<Elem, Tr> &str,
    const base1 &b1)
{
    return str << b1.j;
}

struct derived: virtual base0, base1
{
    derived(int i0, int j0, int k0)
        : base0(i0), base1(j0), k(k0) {}
    int k;
};


template <class Elem, class Tr>
std::basic_ostream<Elem, Tr> &operator <<(
    std::basic_ostream<Elem, Tr> &str,
    const derived &d)
{
    return str << d.k;
}

int main()
{
    Hx::shared_ptr<base0> sp(new derived(1, 2, 3));
    show("base0 shared_ptr", sp);

    Hx::shared_ptr<derived> sp0 =
        Hx::dynamic_pointer_cast<derived>(sp);
    show("upcast from virtual base", sp0);

    Hx::shared_ptr<base1> sp1 =
        Hx::dynamic_pointer_cast<derived>(sp);
    show("cross-cast", sp1);

    Hx::shared_ptr<resource> sp2 =
        Hx::dynamic_pointer_cast<resource>(sp);
    show("failed cast", sp2);

    return 0;
}

