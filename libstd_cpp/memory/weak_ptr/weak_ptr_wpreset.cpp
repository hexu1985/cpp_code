#include "memory.h"
#include "sputil.h"

int main()
{
    Hx::weak_ptr<resource> wp0;
    show("empty object before reset", wp0);

    wp0.reset();
    show("empty object after reset", wp0);

    Hx::shared_ptr<resource> sp1(new resource(1));
    Hx::weak_ptr<resource> wp1(sp1);

    show("non-empty object before reset", wp1);
    wp1.reset();
    show("non-empty object after reset", wp1);

    return 0;
}
