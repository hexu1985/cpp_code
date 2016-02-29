// -*- C++ -*-
// HeXu's
// 2013 Jun

#ifndef HX_LOCK_GUARD_H
#define HX_LOCK_GUARD_H

#include "lock_options.h"

namespace Hx {

/**
 * The class lock_guard is a mutex wrapper that provides 
 * a convenient RAII-style mechanism for owning a mutex 
 * for the duration of a scoped block. 
 * When a lock_guard object is created, 
 * it attempts to take ownership of the mutex it is given. 
 * When control leaves the scope in which the lock_guard object 
 * was created, the lock_guard is destructed and the mutex is released.
 * The lock_guard class is non-copyable. 
 */
template <typename Mutex>
class lock_guard {
private:
	Mutex *mtx_;
	
public:
	typedef Mutex mutex_type;

	/**
	 * Acquires ownership of the given mutex m. 
	 * If m is not a recursive mutex, 
	 * requires that the current thread does not own m. 
	 * Effectively calls m.lock(). 
	 */
	explicit lock_guard(mutex_type &m): mtx_(&m)
	{
		mtx_->lock();
	}

	/**
	 * Acquires ownership of the given mutex m. 
	 * Requires that the current thread owns m.
	 */
	lock_guard(mutex_type &m, adopt_lock_t t): mtx_(&m) {}

	/**
	 * Releases the ownership of the owned mutex. 
	 * Effectively calls m.unlock() where m is the mutex 
	 * passed to the lock_guard's constructor. 
	 */
	~lock_guard()
	{
		mtx_->unlock();
	}
};

}	// namespace Hx

#endif

