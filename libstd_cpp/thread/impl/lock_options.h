// -*- C++ -*-
// HeXu's
// 2013 Jun

#ifndef HX_LOCK_OPTIONS_H
#define HX_LOCK_OPTIONS_H

#include "key_words.h"

namespace Hx {

/**
 * defer_lock_t, try_to_lock_t and adopt_lock_t are empty struct tag types 
 * used to specify locking strategy for lock_guard, unique_lock and shared_lock.
 */
/** do not acquire ownership of the mutex */
struct defer_lock_t {};

/** try to acquire ownership of the mutex without blocking */
struct try_to_lock_t {};

/** assume the calling thread already has ownership of the mutex */
struct adopt_lock_t {};

constexpr defer_lock_t defer_lock = {};
constexpr try_to_lock_t try_to_lock = {};
constexpr adopt_lock_t adopt_lock = {};

}	// namespace Hx

#endif

