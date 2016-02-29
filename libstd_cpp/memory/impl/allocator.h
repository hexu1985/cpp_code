// -*- C++ -*-
// HeXu's
// 2013 Aug

#ifndef HX_ALLOCATOR_H
#define HX_ALLOCATOR_H

#include <cstddef>
#include <cstdlib>
#include <limits>

namespace Hx {

template <typename T>
class allocator;

template <>
struct allocator<void> {
	typedef void value_type;
	typedef void *pointer;
	typedef const void *const_pointer;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	template <typename U>
	struct rebind {
		typedef allocator<U> other;
	};
};

/**
 * Default allocator
 * Allocators are classes that define memory models to be used 
 * by some parts of the Standard Library, and most specifically, 
 * by STL containers.
 */
template <typename T>
struct allocator {
	//type definitions
	typedef T value_type;
	typedef T *pointer;
	typedef const T *const_pointer;
	typedef T &reference;
	typedef const T &const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	//rebind allocator to type U
	template <class U>
	struct rebind {
		typedef allocator<U> other;
	};

	/**
	 * Construct allocator object
	 * Constructs an allocator object.
	 */
	allocator() throw() {}
	allocator(const allocator&) throw() {}

	template <class U>
	allocator(const allocator<U>&) throw() {}

	/**
	 * Allocator destructor
	 * Destructs the allocator object.
	 */
	~allocator() throw() {}

	/**
	 * Return address
	 * Returns the address of x.
	 * In the standard default allocator, this effectively means returning &x.
	 */
	pointer address(reference x) const throw() { return &x; }
	const_pointer address(const_reference x) const throw() { return &x; }

	/**
	 * Allocate block of storage
	 * Attempts to allocate a block of storage with a size large enough 
	 * to contain n elements of member type value_type 
	 * (an alias of the allocator's template parameter), 
	 * and returns a pointer to the first element.
	 */
	pointer allocate(size_type n, allocator<void>::const_pointer hint = NULL)
	{
		return static_cast<pointer>(::operator new(n * sizeof (T)));
	}

	/**
	 * Release block of storage
	 * Releases a block of storage previously allocated with member allocate 
	 * and not yet released.
	 * The elements in the array are not destroyed by a call to 
	 * this member function.
	 * In the default allocator, the block of storage is at some point 
	 * deallocated using ::operator delete (either during the function call, 
	 * or later).
	 */
	void deallocate(pointer p, size_type n)
	{
		::operator delete(static_cast<void *>(p));
	}

	/**
	 * Maximum size possible to allocate
	 * Returns the maximum number of elements, each of member type value_type 
	 * (an alias of allocator's template parameter) that could potentially 
	 * be allocated by a call to member allocate.
	 * A call to member allocate with the value returned by this function 
	 * can still fail to allocate the requested storage.
	 */
	size_type max_size() const throw()
	{
		return std::numeric_limits<size_type>::max() / sizeof (value_type);
	}

	/**
	 * Construct an object
	 * Constructs an element object on the location pointed by p.
	 * Notice that this does not allocate space for the element. It should 
	 * already be available at p (see member allocate to allocate space).
	 */
#if __cplusplus >= 201103L
	template <typename U, typename ...Args>
	void construct(U *p, Args &&...args)
	{
		::new (static_cast<void *>(p)) U(std::forward<Args>(args)...);
	}
#else // !( __cplusplus >= 201103L )
	void construct(pointer p, const_reference val)
	{
		::new (static_cast<void *>(p)) value_type(val);
	}
#endif // __cplusplus >= 201103L

	/**
	 * Destroy an object
	 * Destroys in-place the object pointed by p.
	 * Notice that this does not deallocate the storage for the element 
	 * (see member deallocate to release storage space).
	 */
#if __cplusplus >= 201103L
	template <typename U>
	void destroy(U *p)
	{
		p->~U();
	}
#else // !( __cplusplus >= 201103L )
	void destroy(pointer p)
	{
		p->~value_type();
	}
#endif // __cplusplus >= 201103L
};

template <typename T, typename U>
inline
bool operator ==(const allocator<T> &, const allocator<U> &)
{
	return true;
}

template <typename T>
inline
bool operator ==(const allocator<T> &, const allocator<T> &)
{
	return true;
}

template <typename T, typename U>
inline
bool operator !=(const allocator<T> &, const allocator<U> &)
{
	return false;
}

template <typename T>
inline
bool operator !=(const allocator<T> &, const allocator<T> &)
{
	return false;
}

} // namespace Hx

#endif // HX_ALLOCATOR_H
