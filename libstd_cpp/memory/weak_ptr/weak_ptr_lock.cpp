#include "memory.h"
#include "sputil.h"

static void do_lock(const char *title, Hx::weak_ptr<resource> wp)
{
    Hx::shared_ptr<resource> sp = wp.lock();
    show(title, sp);
}

int main()
{
    Hx::shared_ptr<resource> sp0(new resource);
    Hx::weak_ptr<resource> wp0(sp0);
    do_lock("weak_ptr with resource", wp0);
    sp0.reset();
    do_lock("expired weak_ptr", wp0);

    return 0;
}
