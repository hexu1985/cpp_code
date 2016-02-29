#include "memory.h"
#include "sputil.h"

int main()
{
    Hx::shared_ptr<int> sp;
    show("default constructor", sp);

    return 0;
}
