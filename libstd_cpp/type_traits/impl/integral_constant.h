// -*- C++ -*-
// HeXu's
// 2013 Jul

#ifndef HX_INTEGRAL_CONSTANT_H
#define HX_INTEGRAL_CONSTANT_H

namespace Hx {

template <class T, T v>
struct integral_constant {
	static const T value = v;
	typedef T value_type;
	typedef integral_constant<T, v> type;
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

} // namespace Hx

#endif // HX_INTEGRAL_CONSTANT_H

