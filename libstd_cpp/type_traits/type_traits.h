// -*- C++ -*-
// HeXu's
// 2013 Dec

#ifndef CXX11_TYPE_TRAITS_H
#define CXX11_TYPE_TRAITS_H

#if __cplusplus >= 201103L
#include <type_traits>
#else // !( __cplusplus >= 201103L )
#include <tr1/type_traits>
#endif // __cplusplus >= 201103L

#include "impl/enable_if.h"
#include "impl/integral_constant.h"

#if __cplusplus < 201103L
namespace std {

using namespace std::tr1;

} // namespace cxx11
#endif // __cplusplus < 201103L

#endif // CXX11_TYPE_TRAITS_H
