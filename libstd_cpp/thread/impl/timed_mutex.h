// -*- C++ -*-
// HeXu's
// 2013 Jun

#ifndef	HX_TIMED_MUTEX_H
#define	HX_TIMED_MUTEX_H

#include "mutex.h"
#include "chrono.h"

namespace Hx {

/**
 * Timed mutex class
 * A timed mutex is a time lockable object that is designed to signal when 
 * critical sections of code need exclusive access, just like a regular mutex, 
 * but additionally supporting timed try-lock requests.
 */
class timed_mutex {
	mutex mtx_;

public:
	typedef mutex::native_handle_type native_handle_type; 
	typedef mutex::attribute_type attribute_type;

	/**
	 * Constructs the mutex. 
	 * The mutex is in unlocked state after the call. 
	 */
	timed_mutex(): mtx_() {}
	explicit timed_mutex(const attribute_type &attr): mtx_(attr) {}

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
		// convert rel_time to timespec type
		struct timespec abstime;
		chrono::nanoseconds dur = chrono::nanoseconds(
			chrono::system_clock::now().time_since_epoch()) +
			chrono::nanoseconds(rel_time);
		chrono::seconds sec = 
			chrono::duration_cast<chrono::seconds>(dur);
		abstime.tv_sec = sec.count();
		abstime.tv_nsec = (dur-chrono::nanoseconds(sec)).count();

		return timed_lock(mtx_.native_handle(), &abstime);
	}

	/**
	 * Tries to lock the mutex. Blocks until specified abs_time 
	 * has been reached or the lock is acquired, whichever comes first. 
	 * On successful lock acquisition returns true, otherwise returns false. 
	 */
	template <typename Clock, typename Duration>
	bool try_lock_until(const chrono::time_point<Clock, Duration> &abs_time)
	{
		return try_lock_for(abs_time-Clock::now());
	}

	/** 
	 * Returns the underlying implementation-defined native handle object. 
	 */
	native_handle_type native_handle() { return mtx_.native_handle(); }

private:
	static 
	bool timed_lock(pthread_mutex_t *mutex, const struct timespec *abstime)
	{
		while (true) {
			int err = pthread_mutex_timedlock(mutex, abstime);
			if (err == 0) {
				return true;
			} else if (err == ETIMEDOUT) {
				return false;
			} else if (err == EINTR) {
				continue;
			} else {
				throw system_error(err, system_category(), __func__);
			}
		}
	}
};

}	// namespace Hx

#endif

