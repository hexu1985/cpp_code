#include <iostream>
#include <errno.h>
#include "system_error.h"   // std::error_code, std::generic_category

using namespace std;
using namespace Hx;

int main()
{
	error_code code;
	error_condition cond;

#if __cplusplus >= 201103L
	code = make_error_code(errc(EPIPE));
	cond = errc(EPIPE);
#else
	code = make_error_code(errc::errc_t(EPIPE));
	cond = errc::errc_t(EPIPE);
#endif

	cout << "code.category: " << code.category().name() << "\n";
	cout << "code.message: " << code.message() << "\n";

	cout << "cond.category: " << cond.category().name() << "\n";
	cout << "cond.message: " << cond.message() << "\n";

	if (code == cond) {
		cout << " == \n";
	} else {
		cout << " != \n";
	}

	code = error_code(EPIPE, system_category());

	cout << "code.category: " << code.category().name() << "\n";
	cout << "code.message: " << code.message() << "\n";

	cout << "cond.category: " << cond.category().name() << "\n";
	cout << "cond.message: " << cond.message() << "\n";

	if (code == cond) {
		cout << " == \n";
	} else {
		cout << " != \n";
	}

	return 0;
}
