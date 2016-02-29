// -*- C++ -*-
// HeXu's
// 2014 May

#ifndef HX_BAD_WEAK_PTR_H
#define HX_BAD_WEAK_PTR_H

#include <exception>

namespace Hx {

class bad_weak_ptr: public std::exception {
public:
	virtual const char *what() const noexcept { return "bad_weak_ptr"; }
};

}	// namespace Hx

#endif // HX_BAD_WEAK_PTR_H

