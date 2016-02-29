#ifndef	SPUTIL_H
#define	SPUTIL_H

#include <ostream>
#include <iostream>
#include "memory.h"

struct resource
{
	resource(int i0 = 0): i(i0) {}
	int i;
};

template <class Elem, class Tr>
std::basic_ostream<Elem, Tr> &operator <<(
	std::basic_ostream<Elem, Tr> &str,
	const resource &res)
{
	return str << res.i;
}

class d_res: public resource
{
public:
	d_res(int i0): resource(i0) {}
};

static void show_rc(unsigned long count)
{
	std::cout << " reference count: "
		<< count << '\n';
}

template <class Sp>
void show_refs(const Hx::shared_ptr<Sp> &sp)
{
	show_rc(sp.use_count());
}

template <class Sp>
void show_refs(const Hx::weak_ptr<Sp> &wp)
{
	show_rc(wp.use_count());
}

template <class Sp>
void show_refs(const Sp &)
{}

template <class Sp>
void do_show(const Sp &sp)
{
	std::cout << " pointer: "
		<< (void *) sp.get() << '\n';
	if (sp.get())
		std::cout << " value: " << *sp << '\n';
}

template <class Sp>
void show(const char *title, const Sp &sp)
{
	std::cout << title << '\n';
	show_refs(sp);
	do_show(sp);
}

template <class Ty>
void show(const char *title, 
	const Hx::weak_ptr<Ty> &wp)

{
	std::cout << title << '\n';
	if (wp.expired())
		std::cout << " expired\n";
	else {
		show_refs(wp.use_count());
		do_show(wp.lock());
	}
}

struct instrumented
{
	instrumented()
	{ std::cout << " constructing instrumented\n"; }

	instrumented(const instrumented &)
	{ std::cout << " copy constructing instrumented\n"; }

	instrumented &operator =(const instrumented &)
	{ std::cout << " copying instrumented\n"; return *this; }

	~instrumented()
	{ std::cout << " destroying instrumented\n"; }
};

#endif	// SPUTIL_H
