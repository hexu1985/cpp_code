// -*- C++ -*-
// HeXu's
// 2014 May

#ifndef HX_VECTOR_BASE_H
#define HX_VECTOR_BASE_H

#include <cassert>
#include <cstddef>

#if __cplusplus >= 201103L
#include <type_traits>
#else // !( __cplusplus >= 201103L )
#include "key_words.h"
#include "type_traits.h"
#endif // __cplusplus >= 201103L

namespace Hx {

template <typename SizeType>
class vector_base {
public:
	typedef SizeType size_type;
	static_assert(std::is_integral<size_type>::value, "not support size_type");

private:
	size_type length;	// storage length
	size_type top;		// data end postion

public:
	vector_base() noexcept: length(0), top(0) {}

	vector_base(size_type n) noexcept: length(n), top(0) {}

	size_type size() const noexcept { return top; }

	size_type capacity() const noexcept { return length; }

	/** set size */
	void set_size(size_type n) noexcept
	{ 
		assert(n <= capacity());
		top = n;
	}

	/** set capacity */
	void set_capacity(size_type n) noexcept
	{
		assert(n >= size());
		length = n;
	}

	/** adjust size when push one element back */
	void push_back() noexcept
	{
		assert(!is_full());
		top++;
	}

	/** adjust size when pop one element back */
	void pop_back() noexcept
	{
		assert(!is_empty());
		top--;
	}

	/** adjust size when push n element back */
	void push_back_n(size_type n) noexcept
	{
		assert(size()+n <= capacity());
		top += n;
	}

	/** adjust size when pop n element back */
	void pop_back_n(size_type n) noexcept
	{
		assert(n <= size());
		top -= n;
	}

	/** test if empty */
	bool is_empty() const noexcept { return (top == 0); }

	/** test if full */
	bool is_full() const noexcept { return (top == length); }

	/** the last element's index */
	size_type back() const noexcept { return top-1; }

	/** the index after last element */
	size_type over_back() const noexcept { return top; }
};

}	// namespace Hx

#endif	// HX_VECTOR_BASE_H
