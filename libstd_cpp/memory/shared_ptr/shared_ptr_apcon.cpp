#include "memory.h"
#include "sputil.h"

int main()
{
    std::auto_ptr<resource> ap(new resource(5));
    show("construct auto_ptr from pointer", ap);

#if __cplusplus >= 201103L
    Hx::shared_ptr<resource> sp(std::move(ap));
#else
    Hx::shared_ptr<resource> sp(ap);
#endif
    show("auto_ptr", ap);
    show("shared_ptr", sp);

    return 0;
}
