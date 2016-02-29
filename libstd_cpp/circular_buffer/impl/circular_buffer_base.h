// -*- C++ -*-
// HeXu's
// 2014 Jul

#ifndef HX_CIRCULAR_BUFFER_BASE_H
#define HX_CIRCULAR_BUFFER_BASE_H

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
class circular_buffer_base {
public:
	typedef SizeType size_type;
	static_assert(std::is_integral<size_type>::value, "not support size_type");

private:
	size_type length;	// storage buffer size
	size_type head;		// the index of first element
	size_type tail;		// the index of after last element

public:
	circular_buffer_base() noexcept: length(1), head(0), tail(0) {}

	circular_buffer_base(size_type n) noexcept: length(n+1), head(0), tail(0)
	{}

	size_type size() const noexcept
	{
		return (head > tail ? tail+length-head : tail-head);
	}

	size_type capacity() const noexcept
	{
		return length-1;
	}

	/** set head of circular buffer */
	void set_head(size_type i) noexcept
	{
		head = i;
	}

	void set_size(size_type n) noexcept 
	{
		assert(n <= capacity());
		tail = head+n;
		// adjust tail if tail over length
		tail = (tail < length ? tail : tail-length);
	}

	void set_capacity(size_type n) noexcept
	{
		assert(is_linearized());
		length = n+1;
	}

	/** test if empty */
	bool is_empty() const noexcept { return (head == tail); }

	/** test if full */
	bool is_full() const noexcept
	{
		return (tail+1 == head) || (head == 0 && tail == length-1);
	}

	/** test if linearized */
	bool is_linearized() const noexcept
	{
		return (head <= tail);
	}

	/** return array_one's size if is not linearized */
	size_type array_one_size() const noexcept
	{
		assert(!is_linearized());
		return length-head;
	}

	/** return array_two's size if is not linearized */
	size_type array_two_size() const noexcept
	{
		assert(!is_linearized());
		return tail;
	}

	/** the first element's index */
	size_type front() const noexcept { return head; }

	/** the index before first element */
	size_type under_front() const noexcept 
	{
		return (head  == 0 ? length-1 : head-1);
	}

	/** the last element's index */
	size_type back() const noexcept 
	{
		return (tail == 0 ? length-1 : tail-1);
	}

	/** the index after last element */
	size_type over_back() const noexcept { return tail; }

	/** adjust head when push one element front */
	void push_front() noexcept 
	{
		assert(!is_full());
		head = (head == 0 ? length-1 : head-1);
	}

	/** adjust tail when push one element back */
	void push_back() noexcept
	{
		assert(!is_full());
		tail = (tail == length-1 ? 0 : tail+1);
	}

	/** adjust head when pop one element front */
	void pop_front() noexcept
	{
		assert(!is_empty());
		head = (head == length-1 ? 0 : head+1);
	}

	/** adjust tail when pop one element back */
	void pop_back() noexcept
	{
		assert(!is_empty());
		tail = (tail == 0 ? length-1 : tail-1);
	}

	/** adjust head when push n element front */
	void push_front_n(size_type n) noexcept
	{
		assert(size()+n <= capacity());
		head = backward_n(head, n);
	}

	/** adjust tail when push n element back */
	void push_back_n(size_type n) noexcept
	{
		assert(size()+n <= capacity());
		tail = forward_n(tail, n);
	}

	/** adjust head when pop n element front */
	void pop_front_n(size_type n) noexcept
	{
		assert(n <= size());
		head = forward_n(head, n);
	}

	/** adjust tail when pop n element back */
	void pop_back_n(size_type n) noexcept
	{
		assert(n <= size());
		tail = backward_n(tail, n);
	}

	/** forward n element from start index */
	size_type forward_n(size_type start, size_t n) const noexcept
	{
		assert(n < length);
		return (start+n < length ? start+n : start+n-length);
	}

	/** backward n element from start index */
	size_type backward_n(size_type start, size_t n) const noexcept
	{
		assert(n < length);
		return (start < n ? start+length-n : start-n);
	}

	/** advance n element from start index, n maybe negative */
	size_type advance(size_type start, ptrdiff_t n) const noexcept
	{
		assert(n > -((ptrdiff_t) length) && n < (ptrdiff_t) length);
		if (n > 0) {	// forward
			return forward_n(start, n);
		} else if (n < 0) {	// backward
			return backward_n(start, -n);
		} else {
			return start;
		}
	}

	/** get the offset of pos begin with head */
	size_type offset(size_type pos) const noexcept
	{
		assert(pos < length);
		return pos < head ? pos+length-head : pos-head;
	}
};

}	// namespace Hx

#endif	// HX_CIRCULAR_BUFFER_BASE_H
