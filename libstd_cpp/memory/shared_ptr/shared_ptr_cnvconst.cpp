#include "memory.h"
#include "sputil.h"

int main()
{
    Hx::shared_ptr<const resource> sp(new resource(1));
    show("shared_ptr to const object", sp);
    Hx::shared_ptr<resource> sp0 =
        Hx::const_pointer_cast<resource>(sp);
    show("shared_ptr to non-const object", sp0);

    return 0;
}

