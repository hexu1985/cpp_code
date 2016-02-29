// -*- C++ -*-
// HeXu's
// 2013 Dec

#ifndef HX_INITIALIZER_LIST_H
#define HX_INITIALIZER_LIST_H

#include <stddef.h>

namespace Hx {

template <typename T>
struct initializer_list {
	const T *first;
	const T *last;

	typedef T value_type;
	typedef const T &reference;
	typedef const T &const_reference;
	typedef size_t size_type;
	typedef const T *iterator;
	typedef const T *const_iterator;

	/**
	 * Construct empty initializer_list
	 * Constructs an empty initializer_list object.
	 */
	initializer_list(): first(NULL), last(NULL) {}

	template <size_type N>
	initializer_list(const value_type (&array)[N]) throw()
	{
		first = array;
		last = array+N;
	}

	template <size_type N>
	initializer_list &operator =(const value_type (&array)[N]) throw()
	{
		first = array;
		last = array+N;
		return *this;
	}

	/**
	 * Return size of list
	 * Returns the number of elements in the initializer_list.
	 */
	size_type size() const throw() { return last-first; }

	/**
	 * Return iterator to beginning
	 * Returns a pointer to the first element in the initializer_list.
	 */
	iterator begin() const throw() { return first; }

	/**
	 * Return iterator to end
	 * Returns a pointer to the past-the-end element in the initializer_list.
	 */
	iterator end() const throw() { return last; }
};

}	// namespace Hx

#endif

