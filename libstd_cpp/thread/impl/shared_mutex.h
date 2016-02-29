// -*- C++ -*-
// HeXu's
// 2013 Jun

#ifndef HX_SHARED_MUTEX_H
#define HX_SHARED_MUTEX_H

#include <cassert>
#include <pthread.h>
#include "system_error.h"
#include "shared_mutex_attribute.h"

namespace Hx {

/**
 * The shared_mutex class is a synchronization primitive that can 
 * be used to protect shared data from being simultaneously 
 * accessed by multiple threads. 
 * Differently from other mutex types, there are two levels of access:
 * shared - several threads can share ownership of the same mutex. 
 * exclusive - only one thread can own the mutex. 
 * Shared mutexes are usually used in situations, when multiple readers 
 * can access the same resource at the same time without causing data races, 
 * but only one writer can do so. 
 */
class shared_mutex {
	pthread_rwlock_t rwlck_;

public:
	typedef pthread_rwlock_t native_handle_type;
	typedef shared_mutex_attribute attribute_type;

	/**
	 * Constructs the mutex. 
	 * The mutex is in unlocked state after the call. 
	 */
	shared_mutex()
	{
		int err = pthread_rwlock_init(&rwlck_, NULL);
		if (err != 0) {
			throw system_error(err, system_category(), __func__);
		}
	}

	explicit shared_mutex(const attribute_type &attr)
	{
		int err = pthread_rwlock_init(&rwlck_, attr.native_handle());
		if (err != 0) {
			throw system_error(err, system_category(), __func__);
		}
	}

	/** Destroys the mutex. */
	~shared_mutex()
	{
		int err = pthread_rwlock_destroy(&rwlck_);
		(void) err;
		assert(err == 0);
	}

#if __cplusplus >= 201103L
	shared_mutex(const shared_mutex &) = delete;
	shared_mutex &operator =(const shared_mutex &) = delete;
#else
private:
	shared_mutex(const shared_mutex &);
	shared_mutex &operator =(const shared_mutex &);
public:
#endif

	/** 
	 * locks the mutex, blocks if the mutex is not available 
	 */
	void lock()
	{
		while (true) {
			int err = pthread_rwlock_wrlock(&rwlck_);
			if (err == 0) {
				break;
			} else if (err == EINTR) {
				continue;
			} else {
				throw system_error(err, system_category(), __func__);
			}
		}
	}

	/**
	 * tries to lock the mutex, returns if the mutex is not available
	 */
	bool try_lock()
	{
		int err = pthread_rwlock_trywrlock(&rwlck_);
		if (err == 0) {
			return true;
		} else if (err == EBUSY) {
			return false;
		} else {
			throw system_error(err, system_category(), __func__);
		}
	}

	/**
	 * unlocks the mutex 
	 */
	void unlock()
	{
		int err = pthread_rwlock_unlock(&rwlck_);
		if (err != 0) {
			throw system_error(err, system_category(), __func__);
		}
	}

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

		return timed_wrlock(&rwlck_, &abstime);
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
	 * locks the mutex for shared ownership, 
	 * blocks if the mutex is not available 
	 */
	void lock_shared() 
	{ 
		while (true) {
			int err = pthread_rwlock_rdlock(&rwlck_);
			if (err == 0) {
				break;
			} else if (err == EINTR) {
				continue;
			} else {
				throw system_error(err, system_category(), __func__);
			}
		}
	}

	/**
	 * tries to lock the mutex for shared ownership, 
	 * returns if the mutex is not available 
	 */
	bool try_lock_shared()
	{
		int err = pthread_rwlock_tryrdlock(&rwlck_);
		if (err == 0) {
			return true;
		} else if (err == EBUSY) {
			return false;
		} else {
			throw system_error(err, system_category(), __func__);
		}
	}

	/** unlocks the mutex (shared ownership) */
	void unlock_shared() { unlock(); }

	/**
	 * Tries to lock the mutex for shared ownership. 
	 * Blocks until specified rel_time has elapsed 
	 * or the lock is acquired, whichever comes first. 
	 * On successful lock acquisition returns true, otherwise returns false.
	 */
	template <typename Rep, typename Period>
	bool try_lock_shared_for(const chrono::duration<Rep, Period> &rel_time)
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

		return timed_rdlock(&rwlck_, &abstime);
	}

	/**
	 * Tries to lock the mutex for shared ownership. 
	 * Blocks until specified abs_time has been reached 
	 * or the lock is acquired, whichever comes first. 
	 * On successful lock acquisition returns true, otherwise returns false. 
	 */
	template <typename Clock, typename Duration>
	bool try_lock_shared_until(
		const chrono::time_point<Clock, Duration> &abs_time)
	{
		return try_lock_shared_for(abs_time-Clock::now());
	}

private:
	static 
	bool timed_rdlock(pthread_rwlock_t *rwlock, const struct timespec *abstime)
	{
		while (true) {
			int err = pthread_rwlock_timedrdlock(rwlock, abstime);
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

	static 
	bool timed_wrlock(pthread_rwlock_t *rwlock, const struct timespec *abstime)
	{
		while (true) {
			int err = pthread_rwlock_timedwrlock(rwlock, abstime);
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
