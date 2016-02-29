// -*- C++ -*-
// HeXu's
// 2013 Aug

#ifndef HX_CONDITION_VARIABLE_ANY_H
#define HX_CONDITION_VARIABLE_ANY_H

#include <exception>	// for uncaught_exception
#include "key_words.h"
#include "chrono.h"
#include "lock_guard.h"
#include "unique_lock.h"
#include "mutex.h"
#include "condition_variable.h"

namespace Hx {

/**
 * Condition variable (any lock)
 * Same as condition_variable, 
 * except that its wait functions can take any lockable type as argument 
 * (condition_variable objects can only take unique_lock<mutex>). 
 * Other than that, they are identical.
 */
class condition_variable_any {
private:
	mutex mtx_;	// basic lock on this recursive_mutex
	condition_variable cnd_;	// for threads waiting

public:
	typedef	pthread_cond_t native_handle_type;

	/** Constructs an object of type condition_variable_any. */
	condition_variable_any() {}

#if __cplusplus >= 201103L
	condition_variable_any(const condition_variable_any &) = delete;
	condition_variable_any &operator =(const condition_variable_any &) = delete;
#else
private:
	condition_variable_any(const condition_variable_any &);
	condition_variable_any &operator =(const condition_variable_any &);
public:
#endif

	/** Destroys the object of type condition_variable_any. */
	~condition_variable_any() {}

	/**
	 * Notify one
	 * Unblocks one of the threads currently waiting for this condition.
	 * If no threads are waiting, the function does nothing.
	 * If more than one, it is unspecified which of the threads is selected.
	 */
	void notify_one() noexcept 
	{
		lock_guard<mutex> lck(mtx_);
		cnd_.notify_one(); 
	}

	/**
	 * Notify all
	 * Unblocks all threads currently waiting for this condition.
	 * If no threads are waiting, the function does nothing.
	 */
	void notify_all() noexcept 
	{
		lock_guard<mutex> lck(mtx_);
		cnd_.notify_all(); 
	}

	/**
	 * Wait until notified
	 * The execution of the current thread 
	 * (which shall have locked lck's mutex) is blocked until notified.
	 */
	template <typename Lock>
	void wait(Lock &lck)
	{
		scoped_unlock<Lock> out_lck;
		unique_lock<mutex> in_lck(mtx_); 
		out_lck.unlock(lck);
		cnd_.wait(in_lck);
	}

	/**
	 * If pred is specified, the function only blocks if pred returns false,
	 * and notifications can only unblock the thread when it becomes true 
	 * (which is specially useful to check against spurious wake-up calls). 
	 */
	template <typename Lock, typename Predicate>
	void wait(Lock &lck, Predicate pred)
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
	template <typename Lock, typename Rep, typename Period>
#if __cplusplus >= 201103L
	cv_status 
#else
	cv_status::type 
#endif
	wait_for(Lock &lck, 
		const chrono::duration<Rep, Period> &rel_time)
	{
		scoped_unlock<Lock> out_lck;
		unique_lock<mutex> in_lck(mtx_); 
		out_lck.unlock(lck);
		return cnd_.wait_for(in_lck, rel_time);
	}

	/**
	 * If pred is specified, the function only blocks if pred returns false, 
	 * and notifications can only unblock the thread when it becomes true 
	 * (which is especially useful to check against spurious wake-up calls). 
	 */
	template <typename Lock, typename Rep, typename Period, typename Predicate>
	bool wait_for(Lock &lck, 
		const chrono::duration<Rep, Period> &rel_time, Predicate pred)
	{
		chrono::system_clock::time_point now = chrono::system_clock::now();
#if __cplusplus >= 201103L
		return wait_until(lck, now + rel_time, std::forward<Predicate>(pred));
#else
		return wait_until(lck, 
			now + chrono::system_clock::duration(rel_time), pred);
#endif
	}

	/**
	 * Wait until notified or time point
	 * The execution of the current thread (which shall have locked lck's mutex)
	 * is blocked either until notified or until abs_time, 
	 * whichever happens first.
	 */
	template <typename Lock, typename Clock, typename Duration>
#if __cplusplus >= 201103L
	cv_status 
#else
	cv_status::type 
#endif
	wait_until(Lock &lck, const chrono::time_point<Clock, Duration> &abs_time)
	{
		return wait_for(lck, abs_time - Clock::now());
	}

	/**
	 * If pred is specified, the function only blocks if pred returns false, 
	 * and notifications can only unblock the thread when it becomes true 
	 * (which is especially useful to check against spurious wake-up calls). 
	 */
	template <typename Lock, typename Clock, typename Duration, typename Predicate>
	bool wait_until(Lock &lck, 
		const chrono::time_point<Clock, Duration> &abs_time, Predicate pred)
	{
		while (!pred()) {
			if (wait_until(lck, abs_time) == cv_status::timeout) {
				return pred();
			}
		}
		return true;
	}

private:
	template <typename Mutex>
	class scoped_unlock {
		Mutex *mtx_;

	public:
		scoped_unlock(): mtx_(NULL) {}

		void unlock(Mutex &mtx)
		{
			mtx.unlock();
			mtx_ = &mtx;
		}

		~scoped_unlock()
		{
			if (mtx_) {
				mtx_->lock();
			}
		}
	};
};

}	// namespace Hx

#endif

