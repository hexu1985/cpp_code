#include "memory.h"
#include "sputil.h"

int main()
{
    Hx::shared_ptr<resource> sp0(new resource(0));
    Hx::shared_ptr<resource> sp1(new resource(1));
    show("sp0 before swap", sp0);
    show("sp1 before swap", sp1);

    sp0.swap(sp1);
    show("sp0 after swap", sp0);
    show("sp1 after swap", sp1);

    swap(sp0, sp1);
    show("sp0 after second swap", sp0);
    show("sp1 after second swap", sp1);

    return 0;
}
