// -*- C++ -*-
// HeXu's
// 2013 Jun

#ifndef	HX_TIMED_MUTEX_H
#define	HX_TIMED_MUTEX_H

#include "condition_variable.h"
#include "mutex.h"

namespace Hx {

/**
 * Timed mutex class
 * A timed mutex is a time lockable object that is designed to signal when 
 * critical sections of code need exclusive access, just like a regular mutex, 
 * but additionally supporting timed try-lock requests.
 */
class timed_mutex {
private:
	mutex mtx_;	// basic lock on this recursive_mutex
	condition_variable cnd_;	// for threads waiting
	bool locked_;	// flag of the lock

public:
	/** 
	 * Constructs the mutex. The mutex is in unlocked state after the call. 
	 */
	timed_mutex(): locked_(false) {}

#if __cplusplus >= 201103L
	timed_mutex(const timed_mutex &) = delete;
	timed_mutex &operator =(const timed_mutex &) = delete;
#else
private:
	timed_mutex(const timed_mutex &);
	timed_mutex &operator =(const timed_mutex &);
public:
#endif

	/**
	 * Locks the mutex. If another thread has already locked the mutex, 
	 * a call to lock will block execution until the lock is acquired.
	 * If lock is called by a thread that already owns the mutex, 
	 * the program may deadlock. 
	 */
	void lock()
	{
		unique_lock<mutex> lck(mtx_);

		while (locked_) {
			cnd_.wait(lck);
		}
		locked_ = true;
	}

	/**
	 * Tries to lock the mutex. Returns immediately. 
	 * On successful lock acquisition returns true, otherwise returns false.
	 */
	bool try_lock()
	{
		unique_lock<mutex> lck(mtx_);
		if (locked_) {
			return false;
		}
		locked_ = true;
		return true;
	}

	/**
	 * Tries to lock the mutex. Blocks until specified rel_time 
	 * has elapsed or the lock is acquired, whichever comes first. 
	 * On successful lock acquisition returns true, otherwise returns false. 
	 */
	template <typename Rep, typename Period>
	bool try_lock_for(const chrono::duration<Rep, Period> &rel_time)
	{
		unique_lock<mutex> lck(mtx_);
		while (locked_) {
			if (cnd_.wait_for(lck, rel_time) == cv_status::timeout)
				return false;
		}
		locked_ = true;
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
		unique_lock<mutex> lck(mtx_);
		while (locked_) {
			if (cnd_.wait_until(lck, abs_time) == cv_status::timeout)
				return false;
		}
		locked_ = true;
		return true;
	}

	/**
	 * Unlocks the mutex.
	 * The mutex must be unlocked by all threads that have 
	 * successfully locked it before being destroyed. 
	 */
	void unlock()
	{
		unique_lock<mutex> lck(mtx_);
		locked_ = false;
		cnd_.notify_all();
	}
};

}	// namespace Hx

#endif

