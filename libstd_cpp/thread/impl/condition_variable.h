// -*- C++ -*-
// HeXu's
// 2013 May

#ifndef HX_CONDITION_VARIABLE_H
#define HX_CONDITION_VARIABLE_H

#include <pthread.h>
#include "key_words.h"
#include "chrono.h"
#include "mutex.h"
#include "unique_lock.h"
#include "condition_variable_attribute.h"

namespace Hx {

/**
 * The scoped enumeration cv_status describes whether a timed wait 
 * returned because of timeout or not. 
 */
#if __cplusplus >= 201103L
enum class cv_status { 
#else // !( __cplusplus >= 201103L )
namespace cv_status {
enum type { 
#endif // __cplusplus >= 201103L
	timeout, 
	no_timeout, 
#if __cplusplus >= 201103L
};
#else // !( __cplusplus >= 201103L )
};
}	// namespace cv_status
#endif // __cplusplus >= 201103L

/**
 * The condition_variable class is a synchronization primitive 
 * that can be used to block a thread, or multiple threads 
 * at the same time, until: a notification is received 
 * from another thread, a timeout expires, 
 * or a spurious wakeup occurs.
 * Any thread that intends to wait on condition_variable 
 * has to acquire a unique_lock first. 
 * The wait operations atomically release the mutex 
 * and suspend the execution of the thread. 
 * When the condition variable is notified, 
 * the thread is awakened, and the mutex is reacquired. 
 */
class condition_variable {
	pthread_cond_t cnd_;	// native condition variable

public:
	typedef	pthread_cond_t *native_handle_type;
	typedef condition_variable_attribute attribute_type; 

	/** Constructs an object of type condition_variable. */
	condition_variable()
	{
		int err = pthread_cond_init(&cnd_, NULL);
		if (err != 0) {
			throw system_error(err, system_category(), __func__);
		}
	}

	condition_variable(const attribute_type &attr)
	{
		int err = pthread_cond_init(&cnd_, attr.native_handle());
		if (err != 0) {
			throw system_error(err, system_category(), __func__);
		}
	}

#if __cplusplus >= 201103L
	condition_variable(const condition_variable &) = delete;
	condition_variable &operator =(const condition_variable &) = delete;
#else // !( __cplusplus >= 201103L )
private:
	condition_variable(const condition_variable &);
	condition_variable &operator =(const condition_variable &);
public:
#endif // __cplusplus >= 201103L

	/** Destroys the object of type condition_variable. */
	~condition_variable()
	{
		int err = pthread_cond_destroy(&cnd_); 
		(void) err;
		assert(err == 0);
	}

	/**
	 * Notify one
	 * Unblocks one of the threads currently waiting for this condition.
	 * If no threads are waiting, the function does nothing.
	 * If more than one, it is unspecified which of the threads is selected.
	 */
	void notify_one() noexcept 
	{
		int err = pthread_cond_signal(&cnd_); 
		(void) err;
		assert(err == 0);
	}

	/**
	 * Notify all
	 * Unblocks all threads currently waiting for this condition.
	 * If no threads are waiting, the function does nothing.
	 */
	void notify_all() noexcept 
	{
		int err =pthread_cond_broadcast(&cnd_); 
		(void) err;
		assert(err == 0);
	}

	/**
	 * Wait until notified
	 * The execution of the current thread 
	 * (which shall have locked lck's mutex) is blocked until notified.
	 */
	void wait(unique_lock<mutex> &lck)
	{
		while (true) {
			int err = pthread_cond_wait(&cnd_, lck.mutex()->native_handle());
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
	 * If pred is specified, the function only blocks if pred returns false, 
	 * and notifications can only unblock the thread when it becomes true 
	 * (which is specially useful to check against spurious wake-up calls). 
	 */
	template <typename Predicate>
	void wait(unique_lock<mutex> &lck, Predicate pred)
	{
		while (!pred()) {
			wait(lck);
		}
	}

	/**
	 * Wait for timeout or until notified
	 * The execution of the current thread (which shall have locked lck's mutex)
	 * is blocked during rel_time, or until notified 
	 * (if the latter happens first).
	 */
	template <typename Rep, typename Period>
#if __cplusplus >= 201103L
	cv_status 
#else // !( __cplusplus >= 201103L )
	cv_status::type 
#endif // __cplusplus >= 201103L
	wait_for(unique_lock<mutex> &lck, 
		const chrono::duration<Rep, Period> &rel_time)
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

		return timed_wait(&cnd_, lck.mutex()->native_handle(), &abstime);
	}

	/**
	 * If pred is specified, the function only blocks if pred returns false, 
	 * and notifications can only unblock the thread when it becomes true 
	 * (which is especially useful to check against spurious wake-up calls). 
	 */
	template <typename Rep, typename Period, typename Predicate>
	bool wait_for(unique_lock<mutex> &lck, 
		const chrono::duration<Rep, Period> &rel_time, Predicate pred)
	{
		chrono::system_clock::time_point now = chrono::system_clock::now();
#if __cplusplus >= 201103L
		return wait_until(lck, now+rel_time, std::forward<Predicate>(pred));
#else // !( __cplusplus >= 201103L )
		return wait_until(lck, 
			now+chrono::system_clock::duration(rel_time), pred);
#endif // __cplusplus >= 201103L
	}

	/**
	 * Wait until notified or time point
	 * The execution of the current thread (which shall have locked lck's mutex)
	 * is blocked either until notified or until abs_time, 
	 * whichever happens first.
	 */
	template <typename Clock, typename Duration>
#if __cplusplus >= 201103L
	cv_status 
#else // !( __cplusplus >= 201103L )
	cv_status::type 
#endif // __cplusplus >= 201103L
	wait_until(unique_lock<mutex> &lck, 
		const chrono::time_point<Clock, Duration> &abs_time)
	{
		return wait_for(lck, abs_time-Clock::now());
	}

	/**
	 * If pred is specified, the function only blocks if pred returns false, 
	 * and notifications can only unblock the thread when it becomes true 
	 * (which is especially useful to check against spurious wake-up calls). 
	 */
	template <typename Clock, typename Duration, typename Predicate>
	bool wait_until(unique_lock<mutex> &lck, 
		const chrono::time_point<Clock, Duration> &abs_time, Predicate pred)
	{
		while (!pred()) {
			if (wait_until(lck, abs_time) == cv_status::timeout) {
				return pred();
			}
		}
		return true;
	}

	/** Accesses the native handle of *this. */
	native_handle_type native_handle() { return &cnd_; }

private:
	static
#if __cplusplus >= 201103L
	cv_status 
#else // !( __cplusplus >= 201103L )
	cv_status::type 
#endif // __cplusplus >= 201103L
	timed_wait(pthread_cond_t *cond, pthread_mutex_t *mutex, 
		const struct timespec *abstime)
	{
		while (true) {
			int err = pthread_cond_timedwait(cond, mutex, abstime);
			if (err == 0) {
				return cv_status::no_timeout;
			} else if (err == ETIMEDOUT) {
				return cv_status::timeout;
			} else if (err == EINTR) {
				continue;
			} else {
				throw system_error(err, system_category(), __func__);
			}
		}
	}
};

}	// namespace Hx

#endif // HX_CONDITION_VARIABLE_H

