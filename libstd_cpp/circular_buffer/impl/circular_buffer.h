// -*- C++ -*-
// HeXu's
// 2014 Mar

#ifndef HX_CIRCULAR_BUFFER_H
#define HX_CIRCULAR_BUFFER_H

#include <cassert>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <memory>
#include <limits>
#include <algorithm>

#if __cplusplus >= 201103L
#include <initializer_list>
#include <type_traits>
#else // !( __cplusplus >= 201103L )
#include "key_words.h"
#include "type_traits.h"
#include "algorithm.h"
#endif // __cplusplus >= 201103L

namespace Hx {

template <typename T>
struct circular_buffer_iterator {
	typedef T value_type;
	typedef T *pointer;
	typedef T &reference;
	typedef ptrdiff_t difference_type;
	typedef std::random_access_iterator_tag iterator_category;

	typedef circular_buffer_iterator<T> this_type;
	typedef size_t size_type;

	pointer array;		// storage buffer
	size_type length;	// storage buffer size
	size_type head;		// the index of first element
	size_type pos;		// current position

	circular_buffer_iterator(): array(NULL), length(0), head(0), pos(0) {}

	explicit circular_buffer_iterator(pointer array_, size_type length_, 
		size_type head_, size_type pos_): 
		array(array_), length(length_), head(head_), pos(pos_) 
	{}

	reference operator *() const { return array[pos]; }

	pointer operator ->() const { return array+pos; }

	reference operator [](difference_type n)
	{
		size_type idx = pos;
		advance(idx, n);
		return array[idx];
	}

	this_type &operator ++()	// prefix increment
	{
		next();
		return *this;
	}

	this_type operator ++(int)	// postfix increment
	{
		this_type temp(*this);
		next();
		return temp;
	}

	this_type &operator --()	// prefix decrement
	{
		prev();
		return *this;
	}

	this_type operator --(int)	// postfix decrement
	{
		this_type temp(*this);
		prev();
		return temp;
	}

	this_type &operator +=(difference_type n)
	{
		advance(n);
		return *this;
	}

	this_type &operator -=(difference_type n)
	{
		advance(-n);
		return *this;
	}

	this_type operator +(difference_type n) const
	{
		this_type ret(*this);
		ret += n;
		return ret;
	}

	this_type operator -(difference_type n) const
	{
		this_type ret(*this);
		ret -= n;
		return ret;
	}

	difference_type operator -(const this_type &other) const
	{
		assert(this->array == other.array && this->length == other.length &&
			this->head == other.head);

		return (this->linearized_address() - other.linearized_address());
	}

	bool operator ==(const this_type &other) const
	{
		assert(this->array == other.array && this->length == other.length &&
			this->head == other.head);

		return (this->linearized_address() == other.linearized_address());
	}

	bool operator !=(const this_type &other) const
	{
		return !(*this == other);
	}

	bool operator <(const this_type &other) const
	{
		assert(this->array == other.array && this->length == other.length &&
			this->head == other.head);

		return (this->linearized_address() < other.linearized_address());
	}

	bool operator >(const this_type &other) const
	{
		return !(*this < other && *this == other);
	}

	bool operator <=(const this_type &other) const
	{
		return !(*this > other);
	}

	bool operator >=(const this_type &other) const
	{
		return !(*this < other);
	}

	void next()
	{
		pos = (pos == length-1 ? 0 : pos+1);
	}

	void prev()
	{
		pos = (pos == 0 ? length-1 : pos-1);
	}

	void advance(size_type &idx, difference_type n) const
	{
		if (n >= 0) {	// forward
			n = (n > length ? n%length : n);
			idx = (idx+n >= length ? idx+n-length : idx+n);
		} else { // backward
			n = -n;
			n = (n > length ? n%length : n);
			idx = (idx < n ? idx+length-n : idx-n);
		}
	}

	void advance(difference_type n) { advance(pos, n); }

	size_type offset() const
	{
		return pos < head ? pos+length-head : pos-head;
	}

	pointer linearized_address() const
	{
		return array+offset();
	}
};

template <typename T>
inline
circular_buffer_iterator<T> operator +(ptrdiff_t n, 
	const circular_buffer_iterator<T> &x)
{
	return x+n;
}

template <typename T>
struct circular_buffer_const_iterator {
	typedef T value_type;
	typedef const T *pointer;
	typedef const T &reference;
	typedef ptrdiff_t difference_type;
	typedef std::random_access_iterator_tag iterator_category;

	typedef size_t size_type;
	typedef circular_buffer_const_iterator<T> this_type;
	typedef circular_buffer_iterator<T> iterator;

	pointer array;		// storage buffer
	size_type length;	// storage buffer size
	size_type head;		// the index of first element
	size_type pos;	// current position

	circular_buffer_const_iterator(): array(NULL), length(0), head(0), pos(0) {}

	explicit circular_buffer_const_iterator(pointer array_, size_type length_, 
		size_type head_, size_type pos_): 
		array(array_), length(length_), head(head_), pos(pos_) 
	{}

	circular_buffer_const_iterator(const iterator &iter): 
		array(iter.array), length(iter.length), head(iter.head), pos(iter.pos)
	{}

	reference operator *() const { return array[pos]; }

	pointer operator ->() const { return array+pos; }

	reference operator [](difference_type n)
	{
		size_type idx = pos;
		advance(idx, n);
		return array[idx];
	}

	this_type &operator ++()	// prefix increment
	{
		next();
		return *this;
	}

	this_type operator ++(int)	// postfix increment
	{
		this_type temp(*this);
		next();
		return temp;
	}

	this_type &operator --()	// prefix decrement
	{
		prev();
		return *this;
	}

	this_type operator --(int)	// postfix decrement
	{
		this_type temp(*this);
		prev();
		return temp;
	}

	this_type &operator +=(difference_type n)
	{
		advance(n);
		return *this;
	}

	this_type &operator -=(difference_type n)
	{
		advance(-n);
		return *this;
	}

	this_type operator +(difference_type n) const
	{
		this_type ret(*this);
		ret += n;
		return ret;
	}

	this_type operator -(difference_type n) const
	{
		this_type ret(*this);
		ret -= n;
		return ret;
	}

	difference_type operator -(const this_type &other) const
	{
		assert(this->array == other.array && this->length == other.length &&
			this->head == other.head);

		return (this->linearized_address() - other.linearized_address());
	}

	bool operator ==(const this_type &other) const
	{
		assert(this->array == other.array && this->length == other.length &&
			this->head == other.head);

		return (this->linearized_address() == other.linearized_address());
	}

	bool operator !=(const this_type &other) const
	{
		return !(*this == other);
	}

	bool operator <(const this_type &other) const
	{
		assert(this->array == other.array && this->length == other.length &&
			this->head == other.head);

		return (this->linearized_address() < other.linearized_address());
	}

	bool operator >(const this_type &other) const
	{
		return !(*this < other && *this == other);
	}

	bool operator <=(const this_type &other) const
	{
		return !(*this > other);
	}

	bool operator >=(const this_type &other) const
	{
		return !(*this < other);
	}

	void next()
	{
		pos = (pos == length-1 ? 0 : pos+1);
	}

	void prev()
	{
		pos = (pos == 0 ? length-1 : pos-1);
	}

	void advance(size_type &idx, difference_type n) const
	{
		if (n >= 0) {	// forward
			n = (n > length ? n%length : n);
			idx = (idx+n >= length ? idx+n-length : idx+n);
		} else { // backward
			n = -n;
			n = (n > length ? n%length : n);
			idx = (idx < n ? idx+length-n : idx-n);
		}
	}

	void advance(difference_type n) { advance(pos, n); }

	size_type offset() const
	{
		return pos < head ? pos+length-head : pos-head;
	}

	pointer linearized_address() const
	{
		return array+offset();
	}

	iterator to_iterator()
	{
		return iterator((T *) array, length, head, pos);
	}
};

template <typename T>
inline
circular_buffer_const_iterator<T> operator +(ptrdiff_t n, 
	const circular_buffer_const_iterator<T> &x)
{
	return x+n;
}

template <typename T>
inline
ptrdiff_t operator -(const circular_buffer_iterator<T> &x, 
	const circular_buffer_const_iterator<T> &y)
{
	assert(x.array == y.array && x.length == y.length && x.head == y.head);

	return (x.linearized_address() - y.linearized_address());
}

template <typename T>
inline
bool operator ==(const circular_buffer_iterator<T> &x, 
	const circular_buffer_const_iterator<T> &y)
{
	assert(x.array == y.array && x.length == y.length && x.head == y.head);

	return (x.linearized_address() == y.linearized_address());
}

template <typename T>
inline
bool operator !=(const circular_buffer_iterator<T> &x, 
	const circular_buffer_const_iterator<T> &y)
{
	return !(x == y);
}

template <typename T>
inline
bool operator <(const circular_buffer_iterator<T> &x, 
	const circular_buffer_const_iterator<T> &y)
{
	assert(x.array == y.array && x.length == y.length && x.head == y.head);

	return (x.linearized_address() < y.linearized_address());
}

template <typename T>
inline
bool operator >(const circular_buffer_iterator<T> &x, 
	const circular_buffer_const_iterator<T> &y)
{
	return !(x < y && x == y);
}

template <typename T>
inline
bool operator <=(const circular_buffer_iterator<T> &x, 
	const circular_buffer_const_iterator<T> &y)
{
	return !(x > y);
}

template <typename T>
inline
bool operator >=(const circular_buffer_iterator<T> &x, 
	const circular_buffer_const_iterator<T> &y)
{
	return !(x < y);
}

/* circular_buffer class */
template <typename T, typename Alloc = std::allocator<T> >
class circular_buffer {
public:
	/* Type Definitions of Vectors */
	typedef	T value_type;
	typedef Alloc allocator_type;
	typedef circular_buffer_iterator<T> iterator;
	typedef circular_buffer_const_iterator<T> const_iterator;

#if __cplusplus >= 201103L
	typedef T &reference;
	typedef const T &const_reference;
	typedef typename std::allocator_traits<allocator_type>::pointer pointer;
	typedef typename 
	std::allocator_traits<allocator_type>::const_pointer const_pointer;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef typename 
	std::iterator_traits<iterator>::difference_type difference_type;
	typedef size_t size_type;
#else // !( __cplusplus >= 201103L )
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef typename 
	std::iterator_traits<iterator>::difference_type difference_type;
	typedef size_t size_type;
#endif // __cplusplus >= 201103L

	typedef std::pair<pointer, size_type> array_range;
	typedef std::pair<const_pointer, size_type> const_array_range;

private:
	allocator_type alloc_;
	pointer array_;		// storage buffer
	size_type length_;	// storage buffer size
	size_type head_;	// the index of first element
	size_type tail_;	// the index of after last element

public:
	/**
	 * empty container constructor (default constructor)
	 * Constructs an empty container, with no elements.
	 */
	explicit circular_buffer(const allocator_type &alloc = allocator_type()):
		alloc_(alloc) 
	{
		initialize();
	} 

	/**
	 * fill constructor
	 * Constructs a container with n elements. Each element is a copy of val.
	 */
#if __cplusplus >= 201103L
	explicit circular_buffer(size_type n): 
		circular_buffer(n, value_type(), allocator_type())
	{}
#endif // __cplusplus >= 201103L

#if __cplusplus >= 201103L
	circular_buffer(size_type n, const value_type &val, 
		const allocator_type &alloc = allocator_type()): alloc_(alloc)
#else // !( __cplusplus >= 201103L ) 
	explicit circular_buffer(size_type n, const value_type &val = value_type(), 
		const allocator_type &alloc = allocator_type()): alloc_(alloc)
#endif // __cplusplus >= 201103L
	{
		if (n == 0) {
			initialize();
			return;
		}

		initialize(n);

		try
		{
			uninitialized_fill_n(array_, n, val);
			tail_ = n;
		}
		catch (...)
		{
			finalize();
			throw;
		}
	}

	/**
	 * range constructor
	 * Constructs a container with as many elements as the range [first,last), 
	 * with each element emplace-constructed from its corresponding element 
	 * in that range, in the same order.
	 */
#if __cplusplus >= 201103L
	template <typename InputIterator, typename = typename
		std::enable_if<!std::is_integral<InputIterator>::value>::type>
	circular_buffer(InputIterator first, InputIterator last,
		const allocator_type &alloc = allocator_type()): alloc_(alloc)
#else // !( __cplusplus >= 201103L )
	template <typename InputIterator>
	circular_buffer(InputIterator first, InputIterator last,
		const allocator_type &alloc = allocator_type(), typename
		std::enable_if<!std::is_integral<InputIterator>::value>::type * = NULL):
		alloc_(alloc)
#endif // __cplusplus >= 201103L
	{
		size_type n = std::distance(first, last);
		if (n == 0) {
			initialize();
			return;
		}

		initialize(n);

		try
		{
			uninitialized_copy(first, last, array_);
			tail_ = n;
		}
		catch (...)
		{
			finalize();
			throw;
		}
	}
	
	/**
	 * copy constructor
	 * Constructs a container with a copy of each of the elements in x, 
	 * in the same order.
	 */
	circular_buffer(const circular_buffer &x): alloc_(x.alloc_) 
	{
		size_type n = x.size();
		if (n == 0) {
			initialize();
			return;
		}

		initialize(n);

		try
		{
			uninitialized_copy(x.begin(), x.end(), array_);
			tail_ = n;
		}
		catch (...)
		{
			finalize();
			throw;
		}
	}

	circular_buffer(const circular_buffer &x, const allocator_type &alloc): 
		alloc_(alloc)
	{
		size_type n = x.size();
		if (n == 0) {
			initialize();
			return;
		}

		initialize(n);

		try
		{
			uninitialized_copy(x.begin(), x.end(), array_);
			tail_ = n;
		}
		catch (...)
		{
			finalize();
			throw;
		}
	}

#if __cplusplus >= 201103L
	/**
	 * move constructor (and moving with allocator)
	 * Constructs a container that acquires the elements of x.
	 * If alloc is specified and is different from x's allocator, 
	 * the elements are moved. Otherwise, no elements are constructed 
	 * (their ownership is directly transferred).
	 * x is left in an unspecified but valid state.
	 */
	circular_buffer(circular_buffer &&x): 
		alloc_(std::move(x.alloc_)),
		array_(x.array_), length_(x.length_), head_(x.head_), tail_(x.tail_)
	{
		x.initialize();
	}

	circular_buffer(circular_buffer &&x, const allocator_type &alloc): 
		alloc_(alloc)
	{
		size_type n = x.size();
		if (n == 0) {
			initialize();
			return;
		}

		initialize(n);

		try
		{
			uninitialized_move(x.begin(), x.end(), array_);
			tail_ = n;
		}
		catch (...)
		{
			finalize();
			throw;
		}
	}
#endif // __cplusplus >= 201103L

#if __cplusplus >= 201103L
	/**
	 * initializer list constructor
	 * Constructs a container with a copy of each of the elements in il, 
	 * in the same order.
	 */
	circular_buffer(std::initializer_list<value_type> il,
		const allocator_type &alloc = allocator_type()): 
		circular_buffer(il.begin(), il.end(), alloc) {}
#endif // __cplusplus >= 201103L

	/**
	 * Deque destructor
	 * Destroys the container object.
	 */
	~circular_buffer() { finalize(); }

	/**
	 * The copy assignment 
	 * copies all the elements from x into the container 
	 * (with x preserving its contents).
	 */
	circular_buffer &operator =(const circular_buffer &x)
	{
		if (this == &x)
			return *this;

		assign(x.begin(), x.end());
		return *this;
	}

	/**
	 * The move assignment 
	 * moves the elements of x into the container 
	 * (x is left in an unspecified but valid state).
	 */
#if __cplusplus >= 201103L
	circular_buffer &operator =(circular_buffer &&x)
	{
		if (this == &x)
			return *this;

		this->swap_data(x);
		return *this;
	}
#endif // __cplusplus >= 201103L

	/**
	 * The initializer list assignment 
	 * copies the elements of il into the container.
	 */
#if __cplusplus >= 201103L
	circular_buffer &operator =(std::initializer_list<value_type> il)
	{
		assign(il.begin(), il.end());
		return *this;
	}
#endif // __cplusplus >= 201103L

	/**
	 * Return iterator to beginning
	 * Returns an iterator pointing to the first element 
	 * in the circular_buffer container.
	 */
	iterator begin() noexcept
	{
		return make_iterator(head_);
	}

	const_iterator begin() const noexcept
	{
		return make_const_iterator(head_);
	}

	/**
	 * Return iterator to end
	 * Returns an iterator referring to the past-the-end element 
	 * in the circular_buffer container.
	 */
	iterator end() noexcept
	{
		return make_iterator(tail_);
	}

	const_iterator end() const noexcept
	{
		return make_const_iterator(tail_);
	}

	/**
	 * Return reverse iterator to reverse beginning
	 * Returns a reverse iterator pointing to the last element 
	 * in the circular_buffer (i.e., its reverse beginning).
	 */
	reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

	const_reverse_iterator rbegin() const noexcept 
	{
		return const_reverse_iterator(end()); 
	}

	/**
	 * Return reverse iterator to reverse end
	 * Returns a reverse iterator pointing to the theoretical element 
	 * preceding the first element in the circular_buffer 
	 * (which is considered its reverse end).
	 */
	reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

	const_reverse_iterator rend() const noexcept 
	{
		return const_reverse_iterator(begin()); 
	}

	/**
	 * Return const_iterator to beginning
	 * Returns a const_iterator pointing to the first element 
	 * in the container.
	 */
	const_iterator cbegin() const noexcept
	{
		return make_const_iterator(head_);
	}

	/**
	 * Return const_iterator to end
	 * Returns a const_iterator pointing to the past-the-end element 
	 * in the container.
	 * The value returned shall not be dereferenced.
	 */
	const_iterator cend() const noexcept
	{
		return make_const_iterator(tail_);
	}

	/**
	 * Return const_reverse_iterator to reverse beginning
	 * Returns a const_reverse_iterator pointing to the last element 
	 * in the container (i.e., its reverse beginning).
	 */
	const_reverse_iterator crbegin() const noexcept 
	{
		return const_reverse_iterator(end()); 
	}

	/**
	 * Return const_reverse_iterator to reverse end
	 * Returns a const_reverse_iterator pointing to the theoretical element 
	 * preceding the first element in the container 
	 * (which is considered its reverse end).
	 */
	const_reverse_iterator crend() const noexcept 
	{
		return const_reverse_iterator(begin()); 
	}

	/**
	 * Return size
	 * Returns the number of elements in the circular_buffer container.
	 */
	size_type size() const noexcept
	{
		return head_ > tail_ ? tail_+length_-head_ : tail_-head_;
	}

	/**
	 * Return maximum size
	 * Returns the maximum number of elements that 
	 * the circular_buffer can hold.
	 */
	size_type max_size() const noexcept
	{
		return std::numeric_limits<size_type>::max();
	}

	/**
	 * Return size of allocated storage capacity
	 * Returns the size of the storage space currently allocated 
	 * for the circular_buffer, expressed in terms of elements.
	 */
	size_type capacity() const noexcept 
	{
		return length_ == 0 ? 0 : length_-1;
	}

	/**
	 * Change size
	 * Resizes the container so that it contains n elements.
	 */
	void resize(size_type n)
	{
		resize(n, value_type());
	}

	void resize(size_type n, const value_type &val)
	{
		if (n > capacity()) {
			reserve(adjust_capacity(n));
		}

		size_type sz = size();
		if (sz < n) {	// this->size() < n <= capacity()
			uninitialized_fill(end(), begin()+n, val);
		} else {	// n < this->size()
			range_destroy(begin()+n, end());
		} 

		// update this size
		tail_ = head_;
		forward_n(tail_, n);
	}

	/**
	 * Test whether container is empty
	 * Returns whether the circular_buffer container is empty 
	 * (i.e. whether its size is 0).
	 */
	bool empty() const noexcept { return (head_ == tail_); }

	/**
	 * Test whether circular_buffer is full
	 * Returns whether the circular_buffer is full 
	 * (i.e. whether its size is its capacity).
	 * This function does not modify the container in any way. 
	 */
	bool full() const noexcept
	{
		return (head_ == 0 ? tail_ == length_-1 : tail_+1 == head_) ||
			(length_ == 0);
	}

	/**
	 * Request a change in capacity
	 * Requests that the circular_buffer capacity be at least enough 
	 * to contain n elements.
	 */
	void reserve(size_type n)
	{
		if (n <= capacity()) return;

		// allocate newbuf and remember oldbuf, oldbuf's size and capacity
		pointer new_array = allocate(n+1);
		size_type new_tail = size();

		try
		{
#if __cplusplus >= 201103L
			uninitialized_move(begin(), end(), new_array);
#else // !( __cplusplus >= 201103L )
			uninitialized_copy(begin(), end(), new_array);
#endif // __cplusplus >= 201103L
		}
		catch (...)
		{
			deallocate(new_array, n+1);
			throw;
		}

		finalize();

		array_ = new_array;
		length_ = n+1;
		head_ = 0;
		tail_ = new_tail;
	}

	/**
	 * Shrink to fit
	 * Requests the container to reduce its capacity to fit its size.
	 */
	void shrink_to_fit()
	{
		if (size() > capacity()/2)
			return;

#if __cplusplus >= 201103L
		circular_buffer x(std::move(*this), this->alloc_);
#else // !( __cplusplus >= 201103L )
		circular_buffer x(*this, this->alloc_);
#endif // __cplusplus >= 201103L
		this->swap_data(x);
	}

	/**
	 * Access element
	 * Returns a reference to the element at position n 
	 * in the circular_buffer container.
	 */
	reference operator [](size_type n) 
	{
		size_type pos = head_;
		forward_n(pos, n);
		return array_[pos];
	}

	const_reference operator [](size_type n) const 
	{
		size_type pos = head_;
		forward_n(pos, n);
		return array_[pos];
	}
	
	/**
	 * Access element
	 * Returns a reference to the element at position n 
	 * in the circular_buffer.
	 */
	reference at(size_type n)
	{
		if (n >= size())
			throw std::out_of_range(__func__);
		return this->operator [](n);
	}

	const_reference at(size_type n) const
	{
		if (n >= size())
			throw std::out_of_range(__func__);
		return this->operator [](n);
	}
	
	/**
	 * Access first element
	 * Returns a reference to the first element 
	 * in the circular_buffer container.
	 */
	reference front() { return array_[head_]; }

	const_reference front() const { return array_[head_]; }

	/**
	 * Access last element
	 * Returns a reference to the last element in the container.
	 */
	reference back()
	{
		return tail_ == 0 ? array_[length_-1] : array_[tail_-1];
	}

	const_reference back() const
	{
		return tail_ == 0 ? array_[length_-1] : array_[tail_-1];
	}

	/**
	 * Assign circular_buffer content
	 * Assigns new contents to the circular_buffer, 
	 * replacing its current contents, 
	 * and modifying its size accordingly.
	 */

	/**
	 * In the range version, the new contents are elements constructed from 
	 * each of the elements in the range between first and last, 
	 * in the same order.
	 */
#if __cplusplus >= 201103L
	template <typename InputIterator, typename = typename
		std::enable_if<!std::is_integral<InputIterator>::value>::type>
	void assign(InputIterator first, InputIterator last)
#else // !( __cplusplus >= 201103L )
	template <typename InputIterator>
	void assign(InputIterator first, InputIterator last, typename
		std::enable_if<!std::is_integral<InputIterator>::value>::type * = NULL)
#endif // __cplusplus >= 201103L
	{
		size_type n = std::distance(first, last);
		if (n > capacity()) {
			circular_buffer x(first, last, alloc_);
			this->swap_data(x);
			return;
		}

		// assign elements
		size_type sz = size();
		iterator start = begin();
		std::copy_n(first, std::min(n, sz), start);

		if (sz < n) {	// this->size() < std::distance(first, last)
			std::advance(first, sz);
			uninitialized_copy(first, last, end());
		} else {	// this->size() >= std::distance(first, last)
			range_destroy(start+n, end());
		}

		// update this size
		tail_ = head_;
		forward_n(tail_, n);
	}

	/**
	 * In the fill version, the new contents are n elements, 
	 * each initialized to a copy of val.
	 */
	void assign(size_type n, const value_type &val)
	{
		if (n > capacity()) {
			circular_buffer x(n, val, alloc_);
			this->swap_data(x);
			return;
		}

		// assign elements
		size_type sz = size();
		iterator start = begin();
		std::fill_n(start, std::min(n, sz), val);

		if (sz < n) {	// this->size() < std::distance(first, last)
			uninitialized_fill(start+sz, start+n, val);
		} else if (sz > n) {	// this->size() > std::distance(first, last)
			range_destroy(start+n, end());
		}

		// update this size
		tail_ = head_;
		forward_n(tail_, n);
	}

	/**
	 * In the initializer list version, 
	 * the new contents are copies of the values passed as initializer list, 
	 * in the same order.
	 */
#if __cplusplus >= 201103L
	void assign(std::initializer_list<value_type> il)
	{
		assign(il.begin(), il.end());
	}
#endif // __cplusplus >= 201103L

	/**
	 * Add element at the end
	 * Adds a new element at the end of the circular_buffer container, 
	 * after its current last element. The content of val is copied 
	 * (or moved) to the new element.
	 */
	void push_back(const value_type &val)
	{
		if (full()) {
			reserve(adjust_capacity());
		}

		construct(array_+tail_, val);
		next(tail_);
	}

#if __cplusplus >= 201103L
	void push_back(value_type &&val)
	{
		if (full()) {
			reserve(adjust_capacity());
		}

		construct(array_+tail_, std::forward<value_type>(val));
		next(tail_);
	}
#endif // __cplusplus >= 201103L

	/**
	 * Insert element at beginning
	 * Inserts a new element at the beginning of the circular_buffer container, 
	 * right before its current first element. The content of val is copied 
	 * (or moved) to the inserted element.
	 */
	void push_front(const value_type &val)
	{
		if (full()) {
			reserve(adjust_capacity());
		}

		prev(head_);
		construct(array_+head_, val);
	}

#if __cplusplus >= 201103L
	void push_front(value_type &&val)
	{
		if (full()) {
			reserve(adjust_capacity());
		}

		prev(head_);
		construct(array_+head_, std::forward<value_type>(val));
	}
#endif // __cplusplus >= 201103L

	/**
	 * Delete last element
	 * Removes the last element in the circular_buffer container, 
	 * effectively reducing the container size by one.
	 */
	void pop_back()
	{
		assert(!empty());
		prev(tail_);
		destroy(array_+tail_);
	}

	/**
	 * Delete first element
	 * Removes the first element in the circular_buffer container, 
	 * effectively reducing its size by one.
	 */
	void pop_front()
	{
		assert(!empty());
		destroy(array_+head_);
		next(head_);
	}

	/**
	 * Insert elements
	 * The circular_buffer is extended by inserting new elements 
	 * before the element at the specified position, 
	 * effectively increasing the container size 
	 * by the number of elements inserted.
	 */
	iterator insert(const_iterator position, const value_type &val)
	{
		return insert(position, 1, val);
	}

	iterator insert(const_iterator position, size_type n, const value_type &val)
	{
		assert(position <= end()); 

		if (n == 0)
			return position.to_iterator();

		if (capacity() < size()+n) {	// need reallocate
			reserve(adjust_capacity());
			size_type pos = head_;
			advance(pos, position.offset());
			position = make_const_iterator(pos);
		}

		size_type pos = position.pos;
		if (position.offset() <= size()/2) { // vacate front
			size_type start = head_;
			backward_n(head_, n);
			if (pos == start ||
				vacate_front(make_iterator(pos), make_iterator(start), n)) {
				uninitialized_fill_n(make_iterator(pos)-n, n, val);
			} else {
				std::fill_n(make_iterator(pos)-n, n, val);
			}
			return make_iterator(pos)-n;
		} else {	// vacate back
			size_type finish = tail_;
			forward_n(tail_, n);
			if (pos == finish ||
				vacate_back(make_iterator(pos), make_iterator(finish), n)) {
				uninitialized_fill_n(make_iterator(pos), n, val);
			} else {
				std::fill_n(make_iterator(pos), n, val);
			}
			return make_iterator(pos);
		}
	}

#if __cplusplus >= 201103L
	template <typename InputIterator, typename = typename
		std::enable_if<!std::is_integral<InputIterator>::value>::type>
	iterator insert(const_iterator position, 
		InputIterator first, InputIterator last)
#else // !( __cplusplus >= 201103L )
	template <typename InputIterator>
	iterator insert(const_iterator position, 
		InputIterator first, InputIterator last, typename
		std::enable_if<!std::is_integral<InputIterator>::value>::type * = 0)
#endif // __cplusplus >= 201103L
	{
		assert(position <= end()); 

		size_t n = std::distance(first, last);

		if (n == 0)
			return position.to_iterator();

		if (capacity() < size()+n) {	// need reallocate
			reserve(adjust_capacity());
			size_type pos = head_;
			advance(pos, position.offset());
			position = make_const_iterator(pos);
		}

		size_type pos = position.pos;
		if (position.offset() <= size()/2) { // vacate front
			size_type start = head_;
			backward_n(head_, n);
			if (pos == start ||
				vacate_front(make_iterator(pos), make_iterator(start), n)) {
				uninitialized_copy(first, last, make_iterator(pos)-n);
			} else {
				std::copy(first, last, make_iterator(pos)-n);
			}
			return make_iterator(pos)-n;
		} else {	// vacate back
			size_type finish = tail_;
			forward_n(tail_, n);
			if (pos == finish ||
				vacate_back(make_iterator(pos), make_iterator(finish), n)) {
				uninitialized_copy(first, last, make_iterator(pos));
			} else {
				std::copy(first, last, make_iterator(pos));
			}
			return make_iterator(pos);
		}
	}
	
#if __cplusplus >= 201103L
	iterator insert(const_iterator position, value_type &&val)
	{
		assert(position <= end()); 

		if (full()) {	// need reallocate
			reserve(adjust_capacity());
			size_type pos = head_;
			advance(pos, position.offset());
			position = make_const_iterator(pos);
		}

		size_type pos = position.pos;
		if (position.offset() <= size()/2) { // vacate front
			size_type start = head_;
			prev(head_);
			if (pos == start ||
				vacate_front(make_iterator(pos), make_iterator(start), 1)) {
				construct(make_iterator(pos)-1, std::move(val));
			} else {
				*(make_iterator(pos)-1) = std::move(val);
			}
			return make_iterator(pos)-1;
		} else {	// vacate back
			size_type finish = tail_;
			next(tail_);
			if (pos == finish ||
				vacate_back(make_iterator(pos), make_iterator(finish), 1)) {
				construct(make_iterator(pos), std::move(val));
			} else {
				*make_iterator(pos) = std::move(val);
			}
			return make_iterator(pos);
		}
	}
#endif // __cplusplus >= 201103L

#if __cplusplus >= 201103L
	iterator insert(const_iterator position, 
		std::initializer_list<value_type> il)
	{
		return insert(position, il.begin(), il.end());
	}
#endif // __cplusplus >= 201103L

	/**
	 * Erase elements
	 * Removes from the circular_buffer either a single element (position) 
	 * or a range of elements ([first,last)).
	 */
	iterator erase(const_iterator position)
	{
		assert(!empty() && position <= end());

		if (position == end()) return end();

		if (position.offset() <= size()/2) { // move from front
			iterator start = begin();
			iterator pos = position.to_iterator();
#if __cplusplus >= 201103L
			std::move_backward(start, pos, pos+1);
#else // !( __cplusplus >= 201103L )
			std::copy_backward(start, pos, pos+1);
#endif // __cplusplus >= 201103L
			destroy(start);
			next(head_);
		} else {	// move from back
			iterator pos = position.to_iterator();
			iterator finish = end();
#if __cplusplus >= 201103L
			std::move(pos+1, finish, pos);
#else // !( __cplusplus >= 201103L )
			std::copy(pos+1, finish, pos);
#endif // __cplusplus >= 201103L
			destroy(finish-1);
			prev(tail_);
		}
		return begin()+position.offset();
	}

	iterator erase(const_iterator first, const_iterator last)
	{
		assert(!empty() && first <= last && last <= end());

		if (first == last) 
			return first.to_iterator();

		if (first.offset() <= size()-last.offset()) { // move from front
			iterator start = begin();
#if __cplusplus >= 201103L
			iterator iter = std::move_backward(start, first.to_iterator(),
				last.to_iterator());
#else // !( __cplusplus >= 201103L )
			iterator iter = std::copy_backward(start, first.to_iterator(),
				last.to_iterator());
#endif // __cplusplus >= 201103L
			range_destroy(start, iter);
			forward_n(head_, last-first);
		} else {	// move from back
			iterator finish = end();
#if __cplusplus >= 201103L
			iterator iter = std::move(last.to_iterator(), finish, 
				first.to_iterator());
#else // !( __cplusplus >= 201103L )
			iterator iter = std::copy(last.to_iterator(), finish, 
				first.to_iterator());
#endif // __cplusplus >= 201103L
			range_destroy(iter, finish);
			backward_n(tail_, last-first);
		}
		return begin()+first.offset();
	}

	/**
	 * Swap content
	 * Exchanges the content of the container by the content of x, 
	 * which is another circular_buffer object of the same type.
	 */
	void swap(circular_buffer &x)
	{
		using std::swap;
		this->swap_data(x);
		swap(alloc_, x.alloc_);
	}

	/**
	 * Clear content
	 * Removes all elements from the circular_buffer (which are destroyed), 
	 * leaving the container with a size of 0.
	 */
	void clear() noexcept
	{
		array_range range = array_one();
		range_destroy(range.first, range.first+range.second);
		range = array_two();
		range_destroy(range.first, range.first+range.second);
		tail_ = head_;
	}

#if __cplusplus >= 201103L
	/**
	 * Construct and insert element
	 * The container is extended by inserting a new element at position. 
	 * This new element is constructed in place using args as the arguments 
	 * for its construction.
	 */
	template <typename ... Args>
	iterator emplace(const_iterator position, Args &&... args)
	{
		assert(position <= end()); 

		if (full()) {	// need reallocate
			reserve(adjust_capacity());
			size_type pos = head_;
			advance(pos, position.offset());
			position = make_const_iterator(pos);
		}

		size_type pos = position.pos;
		if (position.offset() <= size()/2) { // vacate front
			size_type start = head_;
			prev(head_);
			if (pos == start ||
				vacate_front(make_iterator(pos), make_iterator(start), 1)) {
				construct(make_iterator(pos)-1, std::forward<Args>(args) ...);
			} else {
				*(make_iterator(pos)-1) = 
					value_type(std::forward<Args>(args) ...);
			}
			return make_iterator(pos)-1;
		} else {	// vacate back
			size_type finish = tail_;
			next(tail_);
			if (pos == finish ||
				vacate_back(make_iterator(pos), make_iterator(finish), 1)) {
				construct(make_iterator(pos), std::forward<Args>(args) ...);
			} else {
				*make_iterator(pos) = value_type(std::forward<Args>(args) ...);
			}
			return make_iterator(pos);
		}
	}

	/**
	 * Construct and insert element at beginning
	 * Inserts a new element at the beginning of the circular_buffer, 
	 * right before its current first element. 
	 * This new element is constructed in place 
	 * using args as the arguments for its construction.
	 */
	template <typename ... Args>
	void emplace_front(Args &&... args)
	{
		if (full()) {
			reserve(adjust_capacity());
		}

		prev(head_);
		construct(array_+head_, std::forward<Args>(args) ...);
	}

	template <typename ... Args>
	void emplace_back(Args &&... args)
	{
		if (full()) {
			reserve(adjust_capacity());
		}

		construct(array_+tail_, std::forward<Args>(args) ...);
		next(tail_);
	}
#endif // __cplusplus >= 201103L

	/**
	 * Get allocator
	 * Returns a copy of the allocator object associated with 
	 * the circular_buffer.
	 */
	allocator_type get_allocator() const noexcept
	{
		return alloc_;
	}

public:
	bool is_linearized() const { return head_ <= tail_; }

	pointer linearize()
	{
		if (!is_linearized()) {
#if __cplusplus >= 201103L
			circular_buffer x(std::move(*this), this->alloc_);
#else // !( __cplusplus >= 201103L )
			circular_buffer x(*this, this->alloc_);
#endif // __cplusplus >= 201103L
			this->swap_data(x);
		}
		return array_+head_;
	}

	array_range array_one()
	{
		if (is_linearized()) {
			return array_range(array_+head_, tail_-head_);
		} else {
			return array_range(array_+head_, length_-head_);
		}
	}

	const_array_range array_one() const 
	{
		if (is_linearized()) {
			return const_array_range(array_+head_, tail_-head_);
		} else {
			return const_array_range(array_+head_, length_-head_);
		}
	}

	array_range array_two()
	{
		if (is_linearized()) {
			return array_range(array_+tail_, 0);
		} else {
			return array_range(array_, tail_);
		}
	}

	const_array_range array_two() const 
	{
		if (is_linearized()) {
			return const_array_range(array_+tail_, 0);
		} else {
			return const_array_range(array_, tail_);
		}
	}

private:
	void next(size_type &pos)
	{
		pos = (pos == length_-1 ? 0 : pos+1);
	}

	void prev(size_type &pos)
	{
		pos = (pos == 0 ? length_-1 : pos-1);
	}

	void advance(size_type &pos, difference_type n)
	{
		if (n >= 0) {	// forward
			n = (n > length_ ? n%length_ : n);
			pos = (pos+n >= length_ ? pos+n-length_ : pos+n);
		} else { // backward
			n = -n;
			n = (n > length_ ? n%length_ : n);
			pos = (pos < n ? pos+length_-n : pos-n);
		}
	}

	void forward_n(size_type &pos, size_type n)
	{
		advance(pos, n);
	}

	void backward_n(size_type &pos, size_type n)
	{
		advance(pos, -static_cast<difference_type>(n));
	}

	size_type adjust_capacity(size_type hint = 0)
	{
		if (hint < 3) hint = 3;
		return std::max(hint, 2*capacity()+1);
	}

	void swap_data(circular_buffer &x)
	{
		std::swap(array_, x.array_);
		std::swap(length_, x.length_);
		std::swap(head_, x.head_);
		std::swap(tail_, x.tail_);
	}

	iterator make_iterator(size_type pos) const {
		return iterator(array_, length_, head_, pos);
	}

	const_iterator make_const_iterator(size_type pos) const {
		return const_iterator(array_, length_, head_, pos);
	}

	/**
	 * vacate n element's space from head for insert before pos.
	 * if uninitialized buffer, return true, otherwise return false
	 */
#if __cplusplus >= 201103L
	bool vacate_front(iterator pos, iterator start, size_type n)
	{
		if (pos-start <= n) {
			uninitialized_move(start, pos, start-n);
			range_destroy(start, pos);
			return true;
		} else {	// pos-start > n
			uninitialized_move_n(start, n, start-n);
			std::move(start+n, pos, start);
			return false;
		}
	}
#else // !( __cplusplus >= 201103L )
	bool vacate_front(iterator pos, iterator start, size_type n)
	{
		if (pos-start <= n) {
			uninitialized_copy(start, pos, start-n);
			range_destroy(start, pos);
			return true;
		} else {	// pos-start > n
			uninitialized_copy_n(start, n, start-n);
			std::copy(start+n, pos, start);
			return false;
		}
	}
#endif // __cplusplus >= 201103L

	/**
	 * vacate n element's space from tail for insert before pos.
	 * if uninitialized buffer, return true, otherwise return false
	 */
#if __cplusplus >= 201103L
	bool vacate_back(iterator pos, iterator finish, size_type n)
	{
		if (finish-pos <= n) {
			uninitialized_move(pos, finish, pos+n);
			range_destroy(pos, finish);
			return true;
		} else {	// finish-pos > n
			uninitialized_move_n(finish-n, n, finish);
			std::move_backward(pos, finish-n, finish);
			return false;
		}
	}
#else // !( __cplusplus >= 201103L )
	bool vacate_back(iterator pos, iterator finish, size_type n)
	{
		if (finish-pos <= n) {
			uninitialized_copy(pos, finish, pos+n);
			range_destroy(pos, finish);
			return true;
		} else {	// finish-pos > n
			uninitialized_copy_n(finish-n, n, finish);
			std::copy_backward(pos, finish-n, finish);
			return false;
		}
	}
#endif // __cplusplus >= 201103L

	pointer allocate(size_type n)
	{
		if (n == 0) {
			return NULL;
		}

#if __cplusplus >= 201103L
		return std::allocator_traits<allocator_type>::allocate(alloc_, n);
#else // !( __cplusplus >= 201103L )
		return alloc_.allocate(n);
#endif // __cplusplus >= 201103L
	}

	void deallocate(pointer p, size_type n)
	{
		if (p == NULL || n == 0)
			return;

#if __cplusplus >= 201103L
		std::allocator_traits<allocator_type>::deallocate(alloc_, p, n);
#else // !( __cplusplus >= 201103L )
		alloc_.deallocate(p, n);
#endif // __cplusplus >= 201103L
	}

#if __cplusplus >= 201103L
	template <typename ...Args>
	void construct(pointer p, Args &&...args)
	{
		std::allocator_traits<allocator_type>::construct(alloc_, p, 
			std::forward<Args>(args)...);
	}

	template <typename ...Args>
	void construct(iterator iter, Args &&...args)
	{
		construct(iter.array+iter.pos, std::forward<Args>(args)...);
	}
#else // !( __cplusplus >= 201103L )
	void construct(pointer p, const value_type &val)
	{
		alloc_.construct(p, val);
	}

	void construct(iterator iter, const value_type &val) 
	{
		construct(iter.array+iter.pos, val);
	}
#endif // __cplusplus >= 201103L

	void destroy(pointer p)
	{
#if __cplusplus >= 201103L
		std::allocator_traits<allocator_type>::destroy(alloc_, p);
#else // !( __cplusplus >= 201103L )
		alloc_.destroy(p);
#endif // __cplusplus >= 201103L
	}

	void destroy(iterator iter)
	{
		destroy(iter.array+iter.pos);
	}

	void range_destroy(pointer first, pointer last)
	{
		while (last != first) {
			destroy(--last);
		}
	}

	void range_destroy(iterator first, iterator last)
	{
		while (last != first) {
			destroy(--last);
		}
	}

	void initialize()
	{
		array_ = NULL;
		length_ = head_ = tail_ = 0;
	}

	void initialize(size_type n)
	{
		array_ = allocate(n+1);
		length_ = n+1;
		head_ = tail_ = 0;
	}

	void finalize()
	{
		range_destroy(begin(), end());
		deallocate(array_, length_);
	}

	template <typename InputIterator, typename OutputIterator>
	OutputIterator uninitialized_copy(InputIterator first, InputIterator last,
		OutputIterator result)
	{
		OutputIterator save(result);
		try
		{
			for (; first != last; ++result, ++first)
				construct(result, value_type(*first));
		}
		catch (...)
		{
			while(save != result)
				destroy(save++);
			throw;
		}
		return result;
	}

#if __cplusplus >= 201103L
	template <typename InputIterator, typename OutputIterator>
	OutputIterator uninitialized_move(InputIterator first, InputIterator last,
		OutputIterator result)
	{
		OutputIterator save(result);
		try
		{
			for (; first != last; ++result, ++first)
				construct(result, std::move(*first));
		}
		catch (...)
		{
			while(save != result)
				destroy(save++);
			throw;
		}
		return result;
	}
#endif // __cplusplus >= 201103L

	template <typename InputIterator, typename OutputIterator>
	OutputIterator uninitialized_copy_n(InputIterator first, size_type n, 
		OutputIterator result)
	{
		OutputIterator save(result);
		try
		{
			for (; n > 0; ++result, ++first, --n)
				construct(result, *first);
		}
		catch (...)
		{
			while(save != result)
				destroy(save++);
			throw;
		}
		return result;
	}

#if __cplusplus >= 201103L
	template <typename InputIterator, typename OutputIterator>
	OutputIterator uninitialized_move_n(InputIterator first, size_type n, 
		OutputIterator result)
	{
		OutputIterator save(result);
		try
		{
			for (; n > 0; ++result, ++first, --n)
				construct(result, std::move(*first));
		}
		catch (...)
		{
			while(save != result)
				destroy(save++);
			throw;
		}
		return result;
	}
#endif // __cplusplus >= 201103L

	template <typename OutputIterator>
	void uninitialized_fill(OutputIterator first, OutputIterator last, 
		const value_type &x)
	{
		OutputIterator save(first);
		try
		{
			for (; first != last; ++first)
				construct(first, x);
		}
		catch (...)
		{
			while(save != first)
				destroy(save++);
			throw;
		}
	}

	template <typename OutputIterator>
	OutputIterator uninitialized_fill_n(OutputIterator first, size_type n, 
		const value_type &x)
	{
		OutputIterator save(first);
		try
		{
			for (; n > 0; ++first, --n)
				construct(first, x);
		}
		catch (...)
		{
			while(save != first)
				destroy(save++);
			throw;
		}
		return first;
	}
};

/**
 * Relational operators for circular_buffer
 * Performs the appropriate comparison operation between 
 * the circular_buffer containers lhs and rhs.
 */
template <typename T, typename Alloc>
bool operator ==(const circular_buffer<T, Alloc> &lhs, 
	const circular_buffer<T, Alloc> &rhs)
{
	if (lhs.size() != rhs.size())
		return false;

	return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T, typename Alloc>
inline
bool operator !=(const circular_buffer<T, Alloc> &lhs, 
	const circular_buffer<T, Alloc> &rhs)
{
	return !(lhs == rhs);
}

template <typename T, typename Alloc>
bool operator <(const circular_buffer<T, Alloc> &lhs, 
	const circular_buffer<T, Alloc> &rhs)
{
	return std::lexicographical_compare(lhs.begin(), lhs.end(),
		rhs.begin(), rhs.end());
}

template <typename T, typename Alloc>
bool operator >(const circular_buffer<T, Alloc> &lhs, 
	const circular_buffer<T, Alloc> &rhs)
{
	return (rhs < lhs);
}

template <typename T, typename Alloc>
bool operator <=(const circular_buffer<T, Alloc> &lhs, 
	const circular_buffer<T, Alloc> &rhs)
{
	return !(lhs > rhs);
}

template <typename T, typename Alloc>
bool operator >=(const circular_buffer<T, Alloc> &lhs, 
	const circular_buffer<T, Alloc> &rhs)
{
	return !(lhs < rhs);
}

/**
 * Exchange contents of circular_buffers
 * The contents of container x are exchanged with those of y. 
 * Both container objects must be of the same type (same template parameters), 
 * although sizes may differ.
 */
template <typename T, typename Alloc>
inline
void swap(circular_buffer<T, Alloc> &x, circular_buffer<T, Alloc> &y)
{
	return x.swap(y);
}

}	// namespace Hx

#endif // HX_CIRCULAR_BUFFER_H

