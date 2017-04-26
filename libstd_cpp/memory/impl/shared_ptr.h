// -*- C++ -*-
// HeXu's
// 2014 May

#ifndef HX_SHARED_PTR_H
#define HX_SHARED_PTR_H

#include <memory>

#include "key_words.h"
#include "shared_count.h"

namespace Hx {

template <typename T>
class shared_ptr;

template <typename T>
class weak_ptr;

template <typename T>
class enable_shared_from_this;

namespace detail {

template <typename T, typename U, typename V>
inline void sp_enable_shared_from_this(const Hx::shared_ptr<T> *sp, const U *p,
	const Hx::enable_shared_from_this<V> *pe)
{
	if (pe != NULL) {
		pe->internal_accept_owner(sp, const_cast<U *>(p));
	}
}

inline void sp_enable_shared_from_this(...)
{
}

template <typename T, typename U>
inline void sp_pointer_construct(Hx::shared_ptr<T> *sp, U *p,
	Hx::detail::shared_count &ref_count)
{
	Hx::detail::shared_count(p).swap(ref_count);
	Hx::detail::sp_enable_shared_from_this(sp, p, p);
}

template <typename T, typename U>
inline void sp_deleter_construct(Hx::shared_ptr<T> *sp, U *p)
{
	Hx::detail::sp_enable_shared_from_this(sp, p, p);
}

}	// namespace detail

template <typename T>
class shared_ptr {
public:
	typedef T element_type;

private:
	element_type *ptr_;
	Hx::detail::shared_count ref_count_;

	typedef shared_ptr<T> this_type;

	template<typename> friend class shared_ptr;
	template<typename> friend class weak_ptr;

public:
	/**
	 * default constructor
	 * The object is empty (owns no pointer, use count of zero).
	 */
#if __cplusplus >= 201103L
	constexpr shared_ptr() noexcept: ptr_(NULL), ref_count_() {}
#else
	shared_ptr() noexcept: ptr_(NULL), ref_count_() {}
#endif

#if __cplusplus >= 201103L
	constexpr shared_ptr(std::nullptr_t): ptr_(NULL), ref_count_() {}
#endif

	/**
	 * construct from pointer
	 * The object owns p, setting the use count to 1.
	 */
	template <typename U>
	explicit shared_ptr(U *p): ptr_(p), ref_count_()
	{
		Hx::detail::sp_pointer_construct(this, p, ref_count_);
	}

	/**
	 * construct from pointer + deleter
	 * the object also takes ownership of deleter del 
	 * (and uses it if at some point needs to delete p).
	 */
	template <typename U, typename D>
	shared_ptr(U *p, D del): ptr_(p), ref_count_(p, del)
	{
		Hx::detail::sp_deleter_construct(this, p);
	}

#if __cplusplus >= 201103L
	template <typename D>
	constexpr shared_ptr(std::nullptr_t, D del): ptr_(NULL), 
		ref_count_((T *) NULL, del) {}
#endif

	/**
	 * construct from pointer + deleter + allocator
	 * any memory needed for internal use is allocated using alloc 
	 * (of which the object keeps a copy, but does not take ownership).
	 */
	template <typename U, typename D, typename Alloc>
	shared_ptr(U *p, D del, Alloc alloc): ptr_(p), ref_count_(p, del, alloc)
	{
		Hx::detail::sp_deleter_construct(this, p);
	}

#if __cplusplus >= 201103L
	template <typename D, typename Alloc>
	constexpr shared_ptr(std::nullptr_t, D del, Alloc alloc): ptr_(NULL), 
		ref_count_((T *) NULL, del, alloc) {}
#endif

	/**
	 * copy constructors
	 * If x is not empty, the object shares ownership of x's assets and 
	 * increases the use count.
	 * If x is empty, an empty object is constructed
	 * (as if default-constructed).
	 */
	shared_ptr(const shared_ptr &x) noexcept: ptr_(x.ptr_), 
		ref_count_(x.ref_count_) {}

	template <typename U>
	shared_ptr(const shared_ptr<U> &x) noexcept: ptr_(x.ptr_), 
		ref_count_(x.ref_count_) {}

	/**
	 * copy from weak_ptr
	 * except that if x has expired, a bad_weak_ptr exception is thrown.
	 */
	template <typename U>
	explicit shared_ptr(const weak_ptr<U> &x): 
		ptr_(x.ptr_), ref_count_(x.ref_count_)
	{}

#if __cplusplus >= 201103L
	/**
	 * move constructors
	 * The object acquires the content managed by x including its owned pointer.
	 * x becomes an empty object (as if default-constructed).
	 */
	shared_ptr(shared_ptr &&x) noexcept: ptr_(x.ptr_), 
		ref_count_(std::move(x.ref_count_))
	{
		x.ptr_ = NULL;
	}

	template <typename U>
	shared_ptr(shared_ptr<U> &&x) noexcept: ptr_(x.ptr_),
		ref_count_(std::move(x.ref_count_))
	{
		x.ptr_ = NULL;
	}

	/**
	 * move from other types of managed pointers
	 * The object acquires the content managed by x and sets the use count to 1.
	 * The ceding object becomes empty, automatically losing ownership of 
	 * the pointer.
	 */
	template <typename U>
	shared_ptr(std::auto_ptr<U> &&x): ptr_(x.get()), ref_count_()
	{
		U *tmp = x.get();
		Hx::detail::shared_count(x).swap(ref_count_);
		Hx::detail::sp_deleter_construct(this, tmp);
	}

	template <typename U, typename D>
	shared_ptr(std::unique_ptr<U, D> &&x): ptr_(x.get()), ref_count_()
	{
		U *tmp = r.get();
		Hx::detail::shared_count(x).swap(ref_count_);
		Hx::detail::sp_deleter_construct(this, tmp);
	}
#else
	template <typename U>
	shared_ptr(std::auto_ptr<U> &x): ptr_(x.get()), ref_count_()
	{
		U *tmp = x.get();
		Hx::detail::shared_count(x).swap(ref_count_);
		Hx::detail::sp_deleter_construct(this, tmp);
	}
#endif

	template <typename U>
	shared_ptr(const shared_ptr<U> &x, element_type *p): ptr_(p), 
		ref_count_(x.ref_count_)
	{}

	/**
	 * shared_ptr assignment
	 * The copy assignments adds the object as a shared owner of x's assets, 
	 * increasing their use_count.
	 */
	shared_ptr &operator =(const shared_ptr &x) noexcept
	{
		this_type(x).swap(*this);
		return *this;
	}

	template <typename U>
	shared_ptr &operator =(const shared_ptr<U> &x) noexcept
	{
		this_type(x).swap(*this);
		return *this;
	}

#if __cplusplus >= 201103L
	/**
	 * The move assignments transfer ownership from x to the shared_ptr 
	 * object without altering the use_count. x becomes an empty shared_ptr 
	 * (as if default-constructed).
	 */
	shared_ptr &operator =(shared_ptr &&x) noexcept
	{
		this_type(std::move(x)).swap(*this);
		return *this;
	}

	template <typename U>
	shared_ptr &operator =(shared_ptr<U> &&x) noexcept
	{
		this_type(std::move(x)).swap(*this);
		return *this;
	}

	/**
	 * the move assignments from other managed pointer types also transfer 
	 * ownership, and are initialized with set a use count of 1.
	 */
	template <typename U>
	shared_ptr &operator =(std::auto_ptr<U> &&x)
	{
		this_type(std::move(x)).swap(*this);
		return *this;
	}

	template <typename U, typename D>
	shared_ptr &operator =(std::unique_ptr<U, D> &&x)
	{
		this_type(std::move(x)).swap(*this);
		return *this;
	}
#else
	template <typename U>
	shared_ptr &operator =(std::auto_ptr<U> &x)
	{
		this_type(x).swap(*this);
		return *this;
	}
#endif

	/**
	 * Swap content
	 * Exchanges the contents of the shared_ptr object with those of x, 
	 * transferring ownership of any managed object between them without 
	 * destroying or altering the use count of either.
	 */
	void swap(shared_ptr &x) noexcept
	{
		std::swap(ptr_, x.ptr_);
		ref_count_.swap(x.ref_count_);
	}

	/**
	 * Reset pointer
	 * the object becomes empty (as if default-constructed).
	 */
	void reset() noexcept
	{
		this_type().swap(*this);
	}

	/**
	 * Reset pointer
	 * the shared_ptr acquires ownership of p with a use count of 1, 
	 * and -optionally- with del and/or alloc as deleter and allocator, 
	 * respectively.
	 */
	template <typename U>
	void reset(U *p)
	{
		this_type(p).swap(*this);
	}

	template <typename U, typename D>
	void reset(U *p, D del)
	{
		this_type(p, del).swap(*this);
	}

	template <typename U, typename D, typename Alloc>
	void reset(U *p, D del, Alloc alloc)
	{
		this_type(p, del, alloc).swap(*this);
	}

	/**
	 * Get pointer
	 * Returns the stored pointer.
	 */
	element_type *get() const noexcept { return ptr_; }

	/**
	 * Dereference object
	 * Returns a reference to the object pointed by the stored pointer.
	 */
	element_type &operator *() const noexcept { return *ptr_; }

	/**
	 * Dereference object member
	 * Returns a pointer to the object pointed by the stored pointer 
	 * in order to access one of its members.
	 */
	element_type *operator ->() const noexcept { return ptr_; }

	/**
	 * Use count
	 * Returns the number of shared_ptr objects that share ownership 
	 * over the same pointer as this object (including it).
	 */
	long int use_count() const noexcept
	{
		return ref_count_.use_count();
	}

	/**
	 * Check if unique
	 * Returns whether the shared_ptr object does not share ownership over 
	 * its pointer with other shared_ptr objects (i.e., it is unique).
	 */
	bool unique() const noexcept
	{
		return ref_count_.unique();
	}

	/**
	 * Check if not null
	 * Returns whether the stored pointer is a null pointer.
	 */
#if __cplusplus >= 201103L
	explicit operator bool() const noexcept
	{
		return !(ptr_ == NULL || ref_count_.empty());
	}
#else
	typedef void (*unspecified_bool_type)();
	static void unspecified_bool_true() {}

	operator unspecified_bool_type() const 
	{
		return !(ptr_ == NULL || ref_count_.empty()) ? unspecified_bool_true : 0; 
	}
#endif

	/**
	 * Owner-based ordering
	 * Returns whether the object is considered to go before x following 
	 * a strict weak owner-based order.
	 */
	template <typename U>
	bool owner_before(const shared_ptr<U> &x) const
	{
		return ref_count_ < x.ref_count_;
	}

	template <typename U>
	bool owner_before(const weak_ptr<U> &x) const
	{
		return ref_count_ < x.ref_count_;
	}

	void *get_deleter() const
	{
		return ref_count_.get_deleter();
	}
};

/**
 * Exchange content of shared_ptr objects
 * Exchanges the contents of x with those of y, transferring ownership of 
 * any managed object between them without destroying either.
 */
template <typename T>
void swap(shared_ptr<T> &x, shared_ptr<T> &y) noexcept
{
	x.swap(y);
}

/**
 * Relational operators ==, !=, <, <=, >, >=
 * Performs the appropriate relational comparison operation between 
 * the shared_ptr objects lhs and rhs, or between a shared_ptr and a nullptr.
 */
template <typename T, typename U>
bool operator ==(const shared_ptr<T> &lhs, const shared_ptr<U> &rhs) noexcept
{
	return lhs.get() == rhs.get();
}

#if __cplusplus >= 201103L
template <typename T>
bool operator ==(const shared_ptr<T> &lhs, std::nullptr_t) noexcept
{
	return lhs.get() == nullptr;
}

template <typename T>
bool operator ==(std::nullptr_t, const shared_ptr<T> &rhs) noexcept
{
	return nullptr == rhs.get();
}
#endif

template <typename T, typename U>
bool operator !=(const shared_ptr<T> &lhs, const shared_ptr<U> &rhs)
{
	return !(lhs == rhs);
}

#if __cplusplus >= 201103L
template <typename T>
bool operator !=(const shared_ptr<T> &lhs, std::nullptr_t) noexcept
{
	return !(lhs == nullptr);
}

template <typename T>
bool operator !=(std::nullptr_t, const shared_ptr<T> &rhs) noexcept
{
	return !(nullptr == rhs);
}
#endif

template <typename T, typename U>
bool operator <(const shared_ptr<T> &lhs, const shared_ptr<U> &rhs) noexcept
{
	return lhs.get() < rhs.get();
}

#if __cplusplus >= 201103L
template <typename T>
bool operator <(const shared_ptr<T> &lhs, std::nullptr_t) noexcept
{
	return lhs.get() < nullptr;
}

template <typename T>
bool operator <(std::nullptr_t, const shared_ptr<T> &rhs) noexcept
{
	return nullptr < rhs.get();
}
#endif

template <typename T, typename U>
bool operator <=(const shared_ptr<T> &lhs, const shared_ptr<U> &rhs) noexcept
{
	return !(lhs.get() > rhs.get());
}

#if __cplusplus >= 201103L
template <typename T>
bool operator <=(const shared_ptr<T> &lhs, std::nullptr_t) noexcept
{
	return !(lhs.get() > nullptr);
}

template <typename T>
bool operator <=(std::nullptr_t, const shared_ptr<T> &rhs) noexcept
{
	return !(nullptr > rhs.get());
}
#endif

template <typename T, typename U>
bool operator >(const shared_ptr<T> &lhs, const shared_ptr<U> &rhs) noexcept
{
	return (rhs < lhs);
}

#if __cplusplus >= 201103L
template <typename T>
bool operator >(const shared_ptr<T> &lhs, std::nullptr_t) noexcept
{
	return (nullptr < lhs);
}

template <typename T>
bool operator >(std::nullptr_t, const shared_ptr<T> &rhs) noexcept
{
	return (rhs < nullptr);
}
#endif

template <typename T, typename U>
bool operator >=(const shared_ptr<T> &lhs, const shared_ptr<U> &rhs) noexcept
{
	return !(lhs < rhs);
}

#if __cplusplus >= 201103L
template <typename T>
bool operator >=(const shared_ptr<T> &lhs, std::nullptr_t) noexcept
{
	return !(lhs < nullptr);
}

template <typename T>
bool operator >=(std::nullptr_t, const shared_ptr<T> &rhs) noexcept
{
	return !(nullptr < rhs);
}
#endif

/**
 * Insert into output stream
 * Writes a system-specific textual representation of the stored pointer value
 */
template <typename charT, typename traits, typename T>
std::basic_ostream<charT, traits> &operator <<(
	std::basic_ostream<charT, traits> &os, const shared_ptr<T> &x)
{
	os << x.get();
	return os;
}

/**
 * Make shared_ptr
 * Allocates and constructs an object of type T passing args to its constructor,
 * and returns an object of type shared_ptr<T> that owns and stores a pointer 
 * to it (with a use count of 1).
 */
#if __cplusplus >= 201103L
template <typename T, typename ...Args>
shared_ptr<T> make_shared(Args &&...args)
{
	return shared_ptr<T>(new T(std::forward<Args>(args)...));
}
#else
template <typename T>
shared_ptr<T> make_shared()
{
	return shared_ptr<T>(new T);
}

template <typename T>
shared_ptr<T> make_shared(const T &val)
{
	return shared_ptr<T>(new T(val));
}
#endif

namespace detail {

template <typename T, typename Alloc>
struct sp_alloc_deleter {
	Alloc alloc;

	sp_alloc_deleter(const Alloc &a): alloc(a) {}
	void operator ()(T *p)
	{
#if __cplusplus >= 201103L
		std::allocator_traits<Alloc>::destroy(alloc, p);
#else
		alloc.destroy(p);
#endif
	}
};

}	// namespace detail

/**
 * Allocate shared_ptr
 * Allocates memory for an object of type T using alloc and 
 * constructs it passing args to its constructor.
 */
#if __cplusplus >= 201103L
template <typename T, typename Alloc, typename ...Args>
shared_ptr<T> allocate_shared(const Alloc &alloc, Args &&...args)
{
	typedef typename Alloc::template rebind<T>::other alloc_type;
	Hx::detail::sp_alloc_deleter<T, alloc_type> deleter(alloc);
	alloc_type allocator(alloc);

	T *p = std::allocator_traits<alloc_type>::allocate(allocator, 1);
	try 
	{
		std::allocator_traits<alloc_type>::construct(allocator, p, 
			std::forward<Args>(args)...);
	}
	catch (...)
	{
		std::allocator_traits<alloc_type>::deallocate(allocator, p, 1);
		throw;
	}

	return shared_ptr<T>(p, deleter, allocator);
}
#else
template <typename T, typename Alloc>
shared_ptr<T> allocate_shared(const Alloc &alloc, const T &val)
{
	typedef typename Alloc::template rebind<T>::other alloc_type;
	Hx::detail::sp_alloc_deleter<T, alloc_type> deleter(alloc);
	alloc_type allocator(alloc);
	
	T *p = allocator.allocate(1);
	try 
	{
		allocator.construct(p, val);
	}
	catch (...)
	{
		allocator.deallocate(p, 1);
		throw;
	}

	return shared_ptr<T>(p, deleter, allocator);
}
#endif

/**
 * Get deleter from shared_ptr
 * Returns a pointer to the deleter owned by sp.
 * If sp has no deleter, and thus would use ::delete to delete 
 * its managed object, the function returns a null pointer.
 */
template <typename D, typename T>
D *get_deleter(const shared_ptr<T> &sp) noexcept
{
	return static_cast<D *>(sp.get_deleter());
}

/**
 * Static cast of shared_ptr
 * Returns a copy of sp of the proper type with its stored pointer 
 * casted statically from U* to T*.
 */
template <typename T, typename U>
shared_ptr<T> static_pointer_cast(const shared_ptr<U> &sp) noexcept
{
	return shared_ptr<T>(sp, static_cast<T *>(sp.get()));
}

/**
 * Dynamic cast of shared_ptr
 * Returns a copy of sp of the proper type with its stored pointer 
 * casted dynamically from U* to T*.
 */
template <typename T, typename U>
shared_ptr<T> dynamic_pointer_cast(const shared_ptr<U> &sp) noexcept
{
	return shared_ptr<T>(sp, dynamic_cast<T *>(sp.get()));
}

/**
 * Const cast of shared_ptr
 * Returns a copy of sp of the proper type with its stored pointer 
 * const casted from U* to T*.
 */
template <typename T, typename U>
shared_ptr<T> const_pointer_cast(const shared_ptr<U> &sp) noexcept
{
	return shared_ptr<T>(sp, const_cast<T *>(sp.get()));
}

} // namespace Hx

#endif	// HX_SHARED_PTR_H

