#include <tr1/memory>
#include <iostream>

#include "sputil.h"

using std::tr1::shared_ptr;
using std::tr1::weak_ptr;

typedef shared_ptr<resource> sps;
typedef weak_ptr<resource> wps;

int main()
{
    sps sp0(new resource(1));
    wps wp0;
    wp0 = sp0;
    show("assign to wp0", wp0);

    sps sp1(new resource(2));
    wps wp1;
    wp1 = sp1;
    show("assign to wp1", wp1);

    wp1 = wp0;
    show("assign, wp0", wp0);
    show("assign, wp1", wp1);
    show("assign, sp0", sp0);
    show("assign, sp1", sp1);

    return 0;
}
