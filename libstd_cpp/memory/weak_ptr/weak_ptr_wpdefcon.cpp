#include "memory.h"
#include "sputil.h"

int main()
{
    Hx::weak_ptr<int> sp;
    show("default constructor", sp);

    return 0;
}

