// -*- C++ -*-
// HeXu's
// 2013 Dec

#ifndef CXX11_FUNCTIONAL_H
#define CXX11_FUNCTIONAL_H

#include "impl/hash_base.h"
#include "impl/hash_string.h"
#include "impl/hash_c_str.h"

#include <functional>

#if __cplusplus < 201103L
#include <tr1/functional>
#endif // __splusplus < 201103L

#if __cplusplus < 201103L
namespace std {

using namespace std::tr1;

} // namespace std
#endif // __splusplus < 201103L

#endif // CXX11_FUNCTIONAL_H 

