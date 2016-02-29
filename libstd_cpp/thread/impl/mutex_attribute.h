// -*- C++ -*-
// HeXu's
// 2014 Jan

#ifndef HX_MUTEX_ATTRIBUTE_H
#define HX_MUTEX_ATTRIBUTE_H

#include <cassert>
#include <pthread.h>
#include "system_error.h"
#include "key_words.h"

namespace Hx {

#if __cplusplus >= 201103L
enum class mutex_type {
#else // !( __cplusplus >= 201103L )
namespace mutex_type {
enum type {
#endif // __cplusplus >= 201103L
	default_option = PTHREAD_MUTEX_DEFAULT,
	recursive = PTHREAD_MUTEX_RECURSIVE,
	error_check = PTHREAD_MUTEX_ERRORCHECK,
	normal = PTHREAD_MUTEX_NORMAL,
#if __cplusplus >= 201103L
};
#else // !( __cplusplus >= 201103L )
};
} // namespace mutex_type
#endif // __cplusplus >= 201103L

class mutex_attribute {
private:
	pthread_mutexattr_t attr_;

public:
	typedef	pthread_mutexattr_t *native_handle_type;
	typedef	const pthread_mutexattr_t *const_native_handle_type;

	explicit mutex_attribute()
	{
		int err = pthread_mutexattr_init(&attr_);
		if (err != 0) {
			throw system_error(err, system_category(), __func__);
		}
	}

	~mutex_attribute()
	{
		int err = pthread_mutexattr_destroy(&attr_);
		(void) err;
		assert(err == 0);
	}

#if __cplusplus >= 201103L
	mutex_attribute(const mutex_attribute &) = delete;
	mutex_attribute &operator =(const mutex_attribute &) = delete;
#else // !( __cplusplus >= 201103L )
private:
	mutex_attribute(const mutex_attribute &);
	mutex_attribute &operator =(const mutex_attribute &);
public:
#endif // __cplusplus >= 201103L

	void set_process_shared(bool pshared = true)
	{
		int err = pthread_mutexattr_setpshared(&attr_, 
			(pshared ? PTHREAD_PROCESS_SHARED : PTHREAD_PROCESS_PRIVATE));
		if (err != 0) {
			throw system_error(err, system_category(), __func__);
		}
	}

	bool is_process_shared() const noexcept
	{
		int pshared;
		int err = pthread_mutexattr_getpshared(&attr_, &pshared);
		(void) err;
		assert(err == 0);
		return (pshared == PTHREAD_PROCESS_SHARED);
	}

#if __cplusplus >= 201103L
	void set_type(mutex_type type)
#else // !( __cplusplus >= 201103L )
	void set_type(mutex_type::type type)
#endif // __cplusplus >= 201103L
	{
		int err = pthread_mutexattr_settype(&attr_, (int) type);
		if (err != 0) {
			throw system_error(err, system_category(), __func__);
		}
	}

#if __cplusplus >= 201103L
	mutex_type get_type() const noexcept
#else // !( __cplusplus >= 201103L )
	mutex_type::type get_type() const noexcept
#endif // __cplusplus >= 201103L
	{
		int type;
		int err = pthread_mutexattr_gettype(&attr_, &type);
		(void) err;
		assert(err == 0);
#if __cplusplus >= 201103L
		return (mutex_type) type;
#else // !( __cplusplus >= 201103L )
		return (mutex_type::type) type;
#endif // __cplusplus >= 201103L
	}

	/** 
	 * Returns the underlying implementation-defined native handle object. 
	 */
	native_handle_type native_handle() noexcept { return &attr_; }
	const_native_handle_type native_handle() const noexcept { return &attr_; }
};

}	// namespace Hx

#endif // HX_MUTEX_ATTRIBUTE_H
