#include <ostream>
#include "memory.h"
#include "sputil.h"

int main()
{
    Hx::shared_ptr<resource> sp(new resource(3));
    show("construct from pointer", sp);

    return 0;
}

