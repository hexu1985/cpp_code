#include "memory.h"
#include "sputil.h"

int main()
{
    Hx::shared_ptr<resource> sp0(new resource(0));
    Hx::weak_ptr<resource> wp0(sp0);
    Hx::shared_ptr<resource> sp1(new resource(1));
    Hx::weak_ptr<resource> wp1(sp1);
    show("wp0 before swap", wp0);
    show("wp1 before swap", wp1);

    wp0.swap(wp1);
    show("wp0 after swap", wp0);
    show("wp1 after swap", wp1);

    swap(wp0, wp1);
    show("wp0 after second swap", wp0);
    show("wp1 after second swap", wp1);

    return 0;
}
