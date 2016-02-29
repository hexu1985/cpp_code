#include <ostream>

#include "memory.h"
#include "sputil.h"

struct C: Hx::enable_shared_from_this<C>, resource
{
    C(int i0= 0): resource(i0) {}
};

static void show_sp(C *cp)
{
    Hx::shared_ptr<C> spc(cp->shared_from_this());
    show("from this", spc);
}

int main()
{
    Hx::shared_ptr<C> sp(new C(1));
    show("original object", sp);
    C *cp = sp.get();
    show_sp(cp);
    show("after return", sp);

    return 0;
}
