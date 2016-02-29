#include "memory.h"
#include <iostream>
#include <string>

typedef Hx::shared_ptr<std::string> stp;

void show(stp s)
{
	if (s)
		std::cout << "string holds '" << *s << "'\n";
	else
		std::cout << "string is empty\n";
}

int main()
{
	stp s;
	show(s);
	s.reset(new std::string("Hello, world"));
	show(s);
	stp p((std::string *) 0);
	show(p);

	return 0;
}
