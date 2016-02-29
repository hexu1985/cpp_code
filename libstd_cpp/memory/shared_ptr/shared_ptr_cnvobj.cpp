#include "memory.h"
#include "sputil.h"

int main()
{
    Hx::shared_ptr<d_res> spa(new d_res(1));
    Hx::weak_ptr<d_res> wpa(spa);

    Hx::shared_ptr<resource> sp0(spa);
    show("shared_ptr constructed from shared_ptr<d_res>",
        sp0);
    Hx::weak_ptr<resource> wp0(spa);
    show("weak_ptr constructed from shared_ptr<d_res>",
        wp0);

    Hx::shared_ptr<resource> sp1(wpa);
    show("shared_ptr constructed from weak_ptr<d_res>",
        sp1);
    Hx::weak_ptr<resource> wp1(wpa);
    show("weak_ptr constructed from weak_ptr<d_res>",
        wp1);

    Hx::shared_ptr<d_res> spb(new d_res(2));
    Hx::weak_ptr<d_res> wpb(spb);

    sp0 = spb;
    show("shared_ptr assigned from shared_ptr<d_res>",
        sp0);
    wp0 = spb;
    show("weak_ptr assigned from shared_ptr<d_res>",
        wp0);
    wp1 = wpb;
    show("weak_ptr assigned from weak_ptr<d_res>",
        wp1);

    return 0;
}
