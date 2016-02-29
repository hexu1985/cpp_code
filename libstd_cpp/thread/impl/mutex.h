// -*- C++ -*-
// HeXu's
// 2013 May

#ifndef HX_MUTEX_H
#define HX_MUTEX_H

#include <pthread.h>
#include "system_error.h"
#include "mutex_attribute.h"

namespace Hx {

/**
 * The mutex class is a synchronization primitive 
 * that can be used to protect shared data 
 * from being simultaneously accessed by multiple threads. 
 */
class mutex {
	pthread_mutex_t mtx_;		// native mutex handle

public:
	typedef	pthread_mutex_t *native_handle_type;
	typedef mutex_attribute attribute_type;

	/**
	 * Constructs the mutex. 
	 * The mutex is in unlocked state after the call. 
	 */
	explicit mutex()
	{
		int err = pthread_mutex_init(&mtx_, NULL);
		if (err != 0) {
			throw system_error(err, system_category(), __func__);
		}
	}

	explicit mutex(const attribute_type &attr)
	{
		int err = pthread_mutex_init(&mtx_, attr.native_handle());
		if (err != 0) {
			throw system_error(err, system_category(), __func__);
		}
	}

	/** Destroys the mutex. */
	~mutex() 
	{
		int err = pthread_mutex_destroy(&mtx_);
		(void) err;
		assert(err == 0);
	}

#if __cplusplus >= 201103L
	mutex(const mutex &) = delete;
	mutex &operator =(const mutex &) = delete;
#else
private:
	mutex(const mutex &);
	mutex &operator =(const mutex &);
public:
#endif

	/**
	 * Locks the mutex. 
	 * If another thread has already locked the mutex, a call to lock will 
	 * block execution until the lock is acquired. If lock is called by a 
	 * thread that already owns the mutex, the program may deadlock. 
	 */
	void lock()
	{
		while (true) {
			int err = pthread_mutex_lock(&mtx_);
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
	 * Tries to lock the mutex. Returns immediately. 
	 * On successful lock acquisition returns true, otherwise returns false.
	 * The behavior is undefined if the mutex is not unlocked 
	 * before being destroyed, i.e. some thread still owns it. 
	 */
	bool try_lock()
	{
		int err = pthread_mutex_trylock(&mtx_);
		if (err == 0) {
			return true;
		} else if (err == EBUSY) {
			return false;
		} else {
			throw system_error(err, system_category(), __func__);
		}
		return false;
	}

	/**
	 * Unlocks the mutex.
	 * The mutex must be unlocked by all threads that have successfully locked 
	 * it before being destroyed. Otherwise, the behavior is undefined. 
	 */
	void unlock()
	{
		int err = pthread_mutex_unlock(&mtx_);
		if (err != 0) {
			throw system_error(err, system_category(), __func__);
		}
	}

	/** 
	 * Returns the underlying implementation-defined native handle object. 
	 */
	native_handle_type native_handle() { return &mtx_; }
};

}	// namespace Hx

#endif // HX_MUTEX_H

