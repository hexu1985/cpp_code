#include "memory.h"
#include "sputil.h"

int main()
{
    Hx::shared_ptr<resource> sp(new resource(4));

    show("shared_ptr", sp);
    Hx::weak_ptr<resource> wp(sp);
    show("weak_ptr", wp);

    return 0;
}
