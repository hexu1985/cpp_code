// -*- C++ -*-
// HeXu's
// 2013 Jun

#ifndef HX_RECURSIVE_TIMED_MUTEX_H
#define HX_RECURSIVE_TIMED_MUTEX_H

#include "timed_mutex.h"
#include "recursive_mutex_attribute.h"

namespace Hx {

/**
 * The recursive_timed_mutex class is a synchronization primitive 
 * that can be used to protect shared data from 
 * being simultaneously accessed by multiple threads.
 * In a manner similar to recursive_mutex, recursive_timed_mutex 
 * provides exclusive, recursive ownership semantics. 
 * In addition, recursive_timed_mutex provides the ability to 
 * attempt to claim ownership of a recursive_timed_mutex 
 * with a timeout via the try_lock_for and try_lock_until methods.
 * The recursive_timed_mutex class is non-copyable. 
 */
class recursive_timed_mutex {
	timed_mutex mtx_;

public:
	typedef timed_mutex::native_handle_type native_handle_type; 
	typedef recursive_mutex_attribute attribute_type;

	/**
	 * Constructs the mutex. 
	 * The mutex is in unlocked state after the call. 
	 */
	explicit recursive_timed_mutex(
		const attribute_type &attr = attribute_type()): mtx_(attr.attribute()) 
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
	 * Tries to lock the mutex. Blocks until specified rel_time 
	 * has elapsed or the lock is acquired, whichever comes first. 
	 * On successful lock acquisition returns true, otherwise returns false.
	 */
	template <typename Rep, typename Period>
	bool try_lock_for(const chrono::duration<Rep, Period> &rel_time)
	{
		return mtx_.try_lock_for(rel_time);
	}

	/**
	 * Tries to lock the mutex. Blocks until specified abs_time 
	 * has been reached or the lock is acquired, whichever comes first. 
	 * On successful lock acquisition returns true, otherwise returns false. 
	 */
	template <typename Clock, typename Duration>
	bool try_lock_until(const chrono::time_point<Clock, Duration> &abs_time)
	{
		return mtx_.try_lock_until(abs_time);
	}

	/** 
	 * Returns the underlying implementation-defined native handle object. 
	 */
	native_handle_type native_handle() { return mtx_.native_handle(); }
};

}	// namespace Hx

#endif

