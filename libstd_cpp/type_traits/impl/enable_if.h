// -*- C++ -*-
// HeXu's
// 2013 Jul

#ifndef HX_ENABLE_IF_H
#define HX_ENABLE_IF_H

namespace Hx {

// Primary template.
/// Define a member typedef @c type only if a boolean constant is true.
template <bool, typename T = void>
struct enable_if {};

// Partial specialization for true.
template <typename T>
struct enable_if<true, T> {
	typedef T type; 
};

} // namespace Hx

#if __cplusplus < 201103L
namespace std {

using Hx::enable_if;

} // namespace std
#endif // __cplusplus < 201103L

#endif // HX_ENABLE_IF_H
