#include "memory.h"
#include <iostream>
 
struct Good: Hx::enable_shared_from_this<Good>
{
    Hx::shared_ptr<Good> getptr() {
        return shared_from_this();
    }
};
 
struct Bad
{
    Hx::shared_ptr<Bad> getptr() {
        return Hx::shared_ptr<Bad>(this);
    }
    ~Bad() { std::cout << "Bad::~Bad() called\n"; }
};
 
int main()
{
    // Good: the two shared_ptr's share the same object
    Hx::shared_ptr<Good> gp1(new Good);
    Hx::shared_ptr<Good> gp2 = gp1->getptr();
    std::cout << "gp2.use_count() = " << gp2.use_count() << '\n';
 
    // Bad, each shared_ptr thinks it's the only owner of the object
    Hx::shared_ptr<Bad> bp1(new Bad);
    Hx::shared_ptr<Bad> bp2 = bp1->getptr();
    std::cout << "bp2.use_count() = " << bp2.use_count() << '\n';
} // UB: double-delete of Bad

/*
Output:

gp2.use_count() = 2
bp2.use_count() = 1
Bad::~Bad() called
Bad::~Bad() called
*** glibc detected *** ./test: double free or corruption
*/
