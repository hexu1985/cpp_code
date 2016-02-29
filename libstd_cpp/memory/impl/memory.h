// -*- C++ -*-
// HeXu's
// 2013 Dec

#ifndef HX_MEMORY_H
#define HX_MEMORY_H

#include <cassert>

#if __cplusplus >= 201103L
#include "uninitialized_move.h"
#endif // __cplusplus < 201103L

#include "uninitialized_copy.h"
#include "uninitialized_copy_n.h"
#include "uninitialized_fill.h"
#include "uninitialized_fill_n.h"
#include "temporary_buffer.h"
#include "allocator.h"
#include "shared_ptr.h"
#include "weak_ptr.h"
#include "enable_shared_from_this.h"

#endif // CXX11_MEMORY_H
