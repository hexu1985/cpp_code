// -*- C++ -*-
// HeXu's
// 2014 May

#ifndef HX_WEAK_PTR_H
#define HX_WEAK_PTR_H

#include "shared_ptr.h"

namespace Hx {

template <typename T>
class weak_ptr {
public:
	typedef T element_type;

private:
	element_type *ptr_;
	Hx::detail::weak_count ref_count_;

	typedef weak_ptr<T> this_type;

	template<typename> friend class shared_ptr;
	template<typename> friend class weak_ptr;

public:
	/**
	 * Construct weak_ptr
	 * constructs empty weak_ptr.
	 */
#if __cplusplus >= 201103L
	constexpr weak_ptr() noexcept: ptr_(NULL), ref_count_() {}
#else
	weak_ptr() noexcept: ptr_(NULL), ref_count_() {}
#endif

	/**
	 * Construct weak_ptr
	 * constructs new weak_ptr which shares an object managed by x.
	 */
	weak_ptr(const weak_ptr &x) noexcept: 
		ptr_(x.ptr_), ref_count_(x.ref_count_)
	{}

	template <typename U>
	weak_ptr(const weak_ptr<U> &x) noexcept: 
		ptr_(x.ptr_), ref_count_(x.ref_count_)
	{}

	template <typename U>
	weak_ptr(const shared_ptr<U> &x) noexcept: 
		ptr_(x.ptr_), ref_count_(x.ref_count_)
	{}

#if __cplusplus >= 201103L
	weak_ptr(weak_ptr &&x) noexcept: 
		ptr_(x.ptr_), ref_count_(std::move(x))
	{
		x.ptr_ = NULL;
	}

	template <typename U>
	weak_ptr(weak_ptr<U> && x) noexcept:
		ptr_(x.ptr_), ref_count_(std::move(x))
	{
		x.ptr_ = NULL;
	}
#endif

	/**
	 * weak_ptr assignment
	 * The object becomes part of the owning group of x, 
	 * giving access to that object's assets until expired 
	 * without taking ownership itself (and without increasing its use count).
	 */
	weak_ptr &operator =(const weak_ptr &x) noexcept
	{
		this_type(x).swap(*this);
		return *this;
	}

	template <typename U>
	weak_ptr &operator =(const weak_ptr<U> &x) noexcept
	{
		this_type(x).swap(*this);
		return *this;
	}

	template <typename U>
	weak_ptr &operator =(const shared_ptr<U> &x) noexcept
	{
		this_type(x).swap(*this);
		return *this;
	}

#if __cplusplus >= 201103L
	weak_ptr &operator =(weak_ptr &&x) noexcept
	{
		this_type(std::move(x)).swap(*this);
		return *this;
	}

	template <typename U>
	weak_ptr &operator =(weak_ptr<U> &&x) noexcept
	{
		this_type(std::move(x)).swap(*this);
		return *this;
	}
#endif

	/**
	 * Swap content
	 * Exchanges the contents of the weak_ptr object with those of x, 
	 * swapping their owning groups and any stored data.
	 */
	void swap(weak_ptr &x) noexcept
	{
		std::swap(ptr_, x.ptr_);
		ref_count_.swap(x.ref_count_);
	}

	/**
	 * Reset pointer
	 * The object becomes empty, as if default constructed.
	 */
	void reset() noexcept
	{
		this_type().swap(*this);
	}

	/**
	 * Use count
	 * Returns the number of shared_ptr objects that share ownership 
	 * over the same pointer as this object.
	 */
	long int use_count() const noexcept
	{
		return ref_count_.use_count();
	}

	/**
	 * Check if expired
	 * Returns whether the weak_ptr object is either empty or there are 
	 * no more shared_ptr in the owner group it belongs to.
	 */
	bool expired() const noexcept
	{
		return ref_count_.use_count() == 0;
	}

	/**
	 * Lock and restore weak_ptr
	 * Returns a shared_ptr with the information preserved 
	 * by the weak_ptr object if it is not expired.
	 */
	shared_ptr<element_type> lock() const noexcept
	{
		if (expired())
			return shared_ptr<element_type>();
		else
			return shared_ptr<element_type>(*this);
	}

	/**
	 * Owner-based ordering
	 * Returns whether the object is considered to go before x following 
	 * a strict weak owner-based order.
	 */
	template <typename U>
	bool owner_before(const weak_ptr<U> &x) const
	{
		return ref_count_ < x.ref_count_;
	}

	template <typename U>
	bool owner_before(const shared_ptr<U> &x) const
	{
		return ref_count_ < x.ref_count_;
	}
};

/**
 * Exchange content of weak_ptr objects
 * Exchanges the contents of x with those of y, swapping their owning 
 * groups and any stored data.
 */
template <typename T>
void swap(weak_ptr<T> &x, weak_ptr<T> &y) noexcept 
{
	x.swap(y);
}

} // namespace Hx

#endif	// HX_WEAK_PTR_H

