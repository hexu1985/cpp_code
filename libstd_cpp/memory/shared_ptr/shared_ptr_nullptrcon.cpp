#include <ostream>
#include "memory.h"

#include "sputil.h"

int main()
{
    Hx::shared_ptr<resource> sp((resource *) 0);
    show("construct from null pointer", sp);

    return 0;
}
