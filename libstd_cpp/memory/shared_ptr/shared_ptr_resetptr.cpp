#include "memory.h"
#include "sputil.h"

class FreeResource {
public:
	void operator ()(resource *res)
	{
		std::cout << "delete resource: ";
		if (res != NULL)
			std::cout << *res;
		std::cout << "\n";
		delete res;
	}
};

int main()
{
    Hx::shared_ptr<resource> sp0;
    show("empty object before reset", sp0);

    sp0.reset(new resource(1), FreeResource());
    show("empty object after reset", sp0);

    sp0.reset(new resource(2), FreeResource());
    show("non-empty object after reset", sp0);

    return 0;
}
