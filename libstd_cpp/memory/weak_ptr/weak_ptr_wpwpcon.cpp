#include "memory.h"
#include "sputil.h"

int main()
{
    Hx::shared_ptr<resource> sp(new resource(4));

    Hx::weak_ptr<resource> wp0(sp);
    Hx::weak_ptr<resource> wp1(wp0);

    show("first weak_ptr", wp0);
    show("second weak_ptr", wp1);

    return 0;
}
