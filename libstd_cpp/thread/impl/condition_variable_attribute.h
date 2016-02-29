// -*- C++ -*-
// HeXu's
// 2014 Jan

#ifndef HX_CONDITION_VARIABLE_ATTRIBUTE_H
#define HX_CONDITION_VARIABLE_ATTRIBUTE_H

#include <cassert>
#include <pthread.h>
#include "system_error.h"
#include "key_words.h"

namespace Hx {

class condition_variable_attribute {
private:
	pthread_condattr_t attr_;

public:
	typedef	pthread_condattr_t *native_handle_type;
	typedef	const pthread_condattr_t *const_native_handle_type;

	explicit condition_variable_attribute()
	{
		int err = pthread_condattr_init(&attr_);
		if (err != 0) {
			throw system_error(err, system_category(), __func__);
		}
	}

	~condition_variable_attribute()
	{
		int err = pthread_condattr_destroy(&attr_);
		(void) err;
		assert(err == 0);
	}

#if __cplusplus >= 201103L
	condition_variable_attribute(const condition_variable_attribute &) = delete;
	condition_variable_attribute &operator =(const condition_variable_attribute &) = delete;
#else // !( __cplusplus >= 201103L )
private:
	condition_variable_attribute(const condition_variable_attribute &);
	condition_variable_attribute &operator =(const condition_variable_attribute &);
public:
#endif // __cplusplus >= 201103L

	void set_process_shared(bool pshared = true)
	{
		int err = pthread_condattr_setpshared(&attr_, 
			(pshared ? PTHREAD_PROCESS_SHARED : PTHREAD_PROCESS_PRIVATE));
		if (err != 0) {
			throw system_error(err, system_category(), __func__);
		}
	}

	bool is_process_shared() const noexcept
	{
		int pshared;
		int err = pthread_condattr_getpshared(&attr_, &pshared);
		(void) err;
		assert(err == 0);
		return (pshared == PTHREAD_PROCESS_SHARED);
	}

	/** 
	 * Returns the underlying implementation-defined native handle object. 
	 */
	native_handle_type native_handle() noexcept { return &attr_; }
	const_native_handle_type native_handle() const noexcept { return &attr_; }
};

} // namespace Hx

#endif // HX_CONDITION_VARIABLE_ATTRIBUTE_H
