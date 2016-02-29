#include "memory.h"
#include <iostream>

struct S {
	int member;
};

int main()
{
	S *s = new S;
	s->member = 4;
	Hx::shared_ptr<S> sp(s);
	std::cout << sp->member << '\n';
	return 0;
}

