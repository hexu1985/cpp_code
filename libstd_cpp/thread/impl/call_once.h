// -*- C++ -*-
// HeXu's
// 2013 May
// modify from boost/thread/pthread/once.hpp

#ifndef HX_CALL_ONCE_H
#define HX_CALL_ONCE_H

#include <pthread.h>
#include <csignal>
#include <cassert>
#include <limits>

#include "key_words.h"
#include "functional.h"

#ifndef	SIG_ATOMIC_MIN
#define	SIG_ATOMIC_MIN std::numeric_limits<sig_atomic_t>::min()
#endif

#ifndef	SIG_ATOMIC_MAX
#define	SIG_ATOMIC_MAX std::numeric_limits<sig_atomic_t>::max()
#endif

namespace Hx {

/**
 * The class once_flag is a helper structure for call_once.
 * An object of type once_flag that is passed to multiple calls to call_once 
 * allows those calls to coordinate with each other such that 
 * only one of the calls will actually run to completion.
 * once_flag is noncopyable. 
 */
class once_flag {
public:
#if __cplusplus >= 201103L
	constexpr once_flag() noexcept: epoch(SIG_ATOMIC_MIN) {}
#else // !( __cplusplus >= 201103L )
	once_flag() noexcept: epoch(SIG_ATOMIC_MIN) {}
#endif // __cplusplus >= 201103L

#if __cplusplus >= 201103L
	template <typename Fn>
	friend void call_once_helper(once_flag &flag, Fn &&fn);
#else // !( __cplusplus >= 201103L )
	template <typename Fn>
	friend void call_once_helper(once_flag &flag, Fn fn);
#endif // __cplusplus >= 201103L

#if __cplusplus >= 201103L
	once_flag(const once_flag &) = delete;
	once_flag &operator =(const once_flag &) = delete;
#else // !( __cplusplus >= 201103L )
private:
	once_flag(const once_flag &);
	once_flag &operator =(const once_flag &);
public:
#endif // __cplusplus >= 201103L

private:
	volatile sig_atomic_t epoch;
};

namespace detail {

class mutex_scoped_lock {
public:
	explicit mutex_scoped_lock(pthread_mutex_t *m): m_(m),locked_(true)
	{
		int err = pthread_mutex_lock(m_); 
		(void) err;
		assert(err == 0);
	}

	void unlock()
	{
		int err = pthread_mutex_unlock(m_);
		(void) err;
		assert(err == 0);
		locked_ = false;
	}
            
	~mutex_scoped_lock()
	{
		if(locked_) {
			unlock();
		}
	}

private:            
	pthread_mutex_t* m_;
	bool locked_;
};

class mutex_scoped_unlock {
public:
	explicit mutex_scoped_unlock(pthread_mutex_t* m): m_(m)
	{
		int err = pthread_mutex_unlock(m_);
		(void) err;
		assert(err == 0);
	}

	~mutex_scoped_unlock()
	{
		int err = pthread_mutex_lock(m_);
		(void) err;
		assert(err == 0);
	}

private:
	pthread_mutex_t* m_;
};

sig_atomic_t &get_once_per_thread_epoch();
extern sig_atomic_t once_global_epoch;
extern pthread_mutex_t once_epoch_mutex;
extern pthread_cond_t once_epoch_cv;

}	// namespace detail

/**
 * Executes the function fn exactly once, even if called from several threads. 
 */
// Based on Mike Burrows fast_pthread_once algorithm as described in
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2444.html
#if __cplusplus >= 201103L
template <typename Fn>
void call_once_helper(once_flag &flag, Fn &&fn)
#else
template <typename Fn>
void call_once_helper(once_flag &flag, Fn fn)
#endif
{
	static const sig_atomic_t uninitialized_flag = SIG_ATOMIC_MIN;
	static const sig_atomic_t being_initialized = uninitialized_flag+1;
	const sig_atomic_t epoch = flag.epoch;
	sig_atomic_t &this_thread_epoch 
		= Hx::detail::get_once_per_thread_epoch();

	int err;
	if (epoch < this_thread_epoch) {
		Hx::detail::mutex_scoped_lock lock(&Hx::detail::once_epoch_mutex);

		while (flag.epoch <= being_initialized) {
			if (flag.epoch == uninitialized_flag) {
				flag.epoch = being_initialized;
				try 
				{
					Hx::detail::mutex_scoped_unlock 
						relocker(&Hx::detail::once_epoch_mutex);
					fn();
				}
				catch (...)
				{
					flag.epoch = uninitialized_flag;
					err = pthread_cond_broadcast(&Hx::detail::once_epoch_cv);
					assert(err == 0);
					(void) err;
					throw;
				}
				flag.epoch = --Hx::detail::once_global_epoch;
				err = pthread_cond_broadcast(&Hx::detail::once_epoch_cv);
				assert(err == 0);
				(void) err;
			} else {
				while (flag.epoch == being_initialized) {
					err = pthread_cond_wait(&Hx::detail::once_epoch_cv,
						&Hx::detail::once_epoch_mutex);
					assert(err == 0);
					(void) err;
				}
			}
		}
		this_thread_epoch = Hx::detail::once_global_epoch;
	}
}

#if __cplusplus >= 201103L
	template <typename Fn, typename ...Args>
	inline
	void call_once(once_flag &flag, Fn &&fn, Args &&...args)
	{
		call_once_helper(flag, 
			std::bind(std::forward<Fn>(fn), std::forward<Args>(args)...));
	}
#else
	template <typename Fn>
	inline
	void call_once(once_flag &flag, Fn fn)
	{
		call_once_helper(flag, fn);
	}

	template <typename Fn, typename A1>
	inline
	void call_once(once_flag &flag, Fn fn, A1 a1)
	{
		call_once_helper(flag, std::bind(fn, a1));
	}

	template <typename Fn, typename A1, typename A2>
	inline
	void call_once(once_flag &flag, Fn fn, A1 a1, A2 a2)
	{
		call_once_helper(flag, std::bind(fn, a1, a2));
	}

	template <typename Fn, typename A1, typename A2, typename A3>
	inline
	void call_once(once_flag &flag, Fn fn, A1 a1, A2 a2, A3 a3)
	{
		call_once_helper(flag, std::bind(fn, a1, a2, a3));
	}

	template <typename Fn, typename A1, typename A2, typename A3, typename A4>
	inline
	void call_once(once_flag &flag, Fn fn, A1 a1, A2 a2, A3 a3, A4 a4)
	{
		call_once_helper(flag, std::bind(fn, a1, a2, a3, a4));
	}
#endif

}	// namespace Hx

#endif

