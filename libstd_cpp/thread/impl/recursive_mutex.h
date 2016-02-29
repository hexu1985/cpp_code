// -*- C++ -*-
// HeXu's
// 2013 Jun

#ifndef HX_RECURSIVE_MUTEX_H
#define HX_RECURSIVE_MUTEX_H

#include "mutex.h"
#include "recursive_mutex_attribute.h"

namespace Hx {

/**
 * The recursive_mutex class is a synchronization primitive 
 * that can be used to protect shared data from being simultaneously 
 * accessed by multiple threads. 
 * recursive_mutex offers exclusive, recursive ownership semantics.
 */
class recursive_mutex {
	mutex mtx_;

public:
	typedef mutex::native_handle_type native_handle_type; 
	typedef recursive_mutex_attribute attribute_type;

	/**
	 * Constructs the mutex. 
	 * The mutex is in unlocked state after the call. 
	 */
	explicit recursive_mutex(const attribute_type &attr = attribute_type()): 
		mtx_(attr.attribute()) 
	{}

	/**
	 * Locks the mutex. 
	 * If another thread has already locked the mutex, a call to lock will 
	 * block execution until the lock is acquired. If lock is called by a 
	 * thread that already owns the mutex, the program may deadlock. 
	 */
	void lock() { mtx_.lock(); }
	
	/**
	 * Tries to lock the mutex. Returns immediately. 
	 * On successful lock acquisition returns true, otherwise returns false.
	 * The behavior is undefined if the mutex is not unlocked 
	 * before being destroyed, i.e. some thread still owns it. 
	 */
	bool try_lock() { return mtx_.try_lock(); }

	/**
	 * Unlocks the mutex.
	 * The mutex must be unlocked by all threads that have successfully locked 
	 * it before being destroyed. Otherwise, the behavior is undefined. 
	 */
	void unlock() { mtx_.unlock(); }

	/** 
	 * Returns the underlying implementation-defined native handle object. 
	 */
	native_handle_type native_handle() { return mtx_.native_handle(); }
};

}	// namespace Hx

#endif

