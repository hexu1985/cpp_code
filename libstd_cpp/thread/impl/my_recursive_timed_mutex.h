// -*- C++ -*-
// HeXu's
// 2013 Jun

#ifndef HX_RECURSIVE_TIMED_MUTEX_H
#define HX_RECURSIVE_TIMED_MUTEX_H

#include "chrono.h"
#include "my_recursive_mutex.h"

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
class recursive_timed_mutex: public recursive_mutex {
public:
	/** 
	 * Constructs the mutex. The mutex is in unlocked state after the call. 
	 */
	recursive_timed_mutex(): recursive_mutex() {}

#if __cplusplus >= 201103L
	recursive_timed_mutex(const recursive_timed_mutex &) = delete;
	recursive_timed_mutex &operator =(const recursive_timed_mutex &) = delete;
#else
private:
	recursive_timed_mutex(const recursive_timed_mutex &);
	recursive_timed_mutex &operator =(const recursive_timed_mutex &);
public:
#endif
	/**
	 * Tries to lock the mutex. Blocks until specified rel_time 
	 * has elapsed or the lock is acquired, whichever comes first. 
	 * On successful lock acquisition returns true, otherwise returns false.
	 */
	template <typename Rep, typename Period>
	bool try_lock_for(const chrono::duration<Rep, Period> &rel_time)
	{
		unique_lock<mutex> lock(mtx_);
		thread_id current_tid = this_thread::get_id();
		if (locked_depth_ > 0 && current_tid == owner_tid_) {
			locked_depth_++;		// already got lock
			return true;
		}

		while (locked_depth_ != 0) {	// wait for other unlock
			if (cnd_.wait_for(lock, rel_time) == cv_status::timeout)
				return false;
		}

		locked_depth_ = 1;
		owner_tid_ = current_tid;
		return true;
	}

	/**
	 * Tries to lock the mutex. Blocks until specified abs_time 
	 * has been reached or the lock is acquired, whichever comes first. 
	 * On successful lock acquisition returns true, otherwise returns false.
	 */
	template <typename Clock, typename Duration>
	bool try_lock_until(const chrono::time_point<Clock, Duration> &abs_time)
	{
		unique_lock<mutex> lock(mtx_);
		thread_id current_tid = this_thread::get_id();
		if (locked_depth_ > 0 && current_tid == owner_tid_) {
			locked_depth_++;		// already got lock
			return true;
		}

		while (locked_depth_ != 0) {	// wait for other unlock
			if (cnd_.wait_until(lock, abs_time) == cv_status::timeout)
				return false;
		}

		locked_depth_ = 1;
		owner_tid_ = current_tid;
		return true;
	}
};

}	// namespace Hx

#endif

