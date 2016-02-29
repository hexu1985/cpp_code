#include "memory.h"
#include "sputil.h"

int main()
{
    Hx::shared_ptr<resource> sp0(new resource(4));

    show("construct from pointer", sp0);
    Hx::shared_ptr<resource> sp1(sp0);

    show("construct from shared_ptr object", sp1);
    show("after copying", sp0);

    return 0;
}
