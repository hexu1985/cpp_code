// -*- C++ -*-
// HeXu's
// 2014 Jan

#ifndef HX_RECURSIVE_MUTEX_ATTRIBUTE_H
#define HX_RECURSIVE_MUTEX_ATTRIBUTE_H

#include "mutex_attribute.h"

namespace Hx {

class recursive_mutex_attribute {
private:
	mutex_attribute attr_;

public:
	typedef	mutex_attribute::native_handle_type native_handle_type;
	typedef	mutex_attribute::const_native_handle_type const_native_handle_type;

	explicit recursive_mutex_attribute(): attr_()
	{
		attr_.set_type(mutex_type::recursive);
	}

	~recursive_mutex_attribute() {}

	mutex_attribute &attribute() noexcept { return attr_; }
	const mutex_attribute &attribute() const noexcept { return attr_; }

#if __cplusplus >= 201103L
	recursive_mutex_attribute(const recursive_mutex_attribute &) = delete;
	recursive_mutex_attribute &operator =(const recursive_mutex_attribute &) = delete;
#else // !( __cplusplus >= 201103L )
private:
	recursive_mutex_attribute(const recursive_mutex_attribute &);
	recursive_mutex_attribute &operator =(const recursive_mutex_attribute &);
public:
#endif // __cplusplus >= 201103L

	void set_process_shared(bool pshared = true)
	{
		attr_.set_process_shared(pshared);
	}

	bool is_process_shared() const noexcept
	{
		return attr_.is_process_shared();
	}

	/** 
	 * Returns the underlying implementation-defined native handle object. 
	 */
	native_handle_type native_handle() noexcept 
	{
		return attr_.native_handle(); 
	}

	const_native_handle_type native_handle() const noexcept 
	{
		return attr_.native_handle(); 
	}
};

}	// namespace Hx

#endif // HX_RECURSIVE_MUTEX_ATTRIBUTE_H
