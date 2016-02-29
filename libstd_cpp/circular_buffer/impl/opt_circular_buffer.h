// -*- C++ -*-
// HeXu's
// 2014 Mar

#ifndef HX_OPT_CIRCULAR_BUFFER_H
#define HX_OPT_CIRCULAR_BUFFER_H

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

#include "circular_buffer_base.h"

namespace Hx {

namespace opt {

template <typename T, typename SizeType = size_t>
struct circular_buffer_iterator {
	typedef T value_type;
	typedef T *pointer;
	typedef T &reference;
	typedef ptrdiff_t difference_type;
	typedef std::random_access_iterator_tag iterator_category;

	typedef circular_buffer_iterator<T, SizeType> this_type;
	typedef SizeType size_type;
	typedef circular_buffer_base<size_type> space_manager_type;

	pointer arr;		// storage buffer
	space_manager_type *sm;	// space manager
	size_type pos;		// current position

	circular_buffer_iterator(): arr(NULL), sm(NULL), pos(0) {}

	explicit circular_buffer_iterator(pointer arr_, space_manager_type *sm_,
		size_type pos_): arr(arr_), sm(sm_), pos(pos_) 
	{}

	reference operator *() const { return arr[pos]; }

	pointer operator ->() const { return arr+pos; }

	reference operator [](difference_type n)
	{
		return arr[sm->advance(pos, n)];
	}

	this_type &operator ++()	// prefix increment
	{
		pos = sm->forward_n(pos, 1);
		return *this;
	}

	this_type operator ++(int)	// postfix increment
	{
		this_type temp(*this);
		pos = sm->forward_n(pos, 1);
		return temp;
	}

	this_type &operator --()	// prefix decrement
	{
		pos = sm->backward_n(pos, 1);
		return *this;
	}

	this_type operator --(int)	// postfix decrement
	{
		this_type temp(*this);
		pos = sm->backward_n(pos, 1);
		return temp;
	}

	this_type &operator +=(difference_type n)
	{
		pos = sm->advance(pos, n);
		return *this;
	}

	this_type &operator -=(difference_type n)
	{
		pos = sm->advance(pos, -n);
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
		return (this->linearized_address() - other.linearized_address());
	}

	bool operator ==(const this_type &other) const
	{
		return (arr == other.arr && sm == other.sm && pos == other.pos);
	}

	bool operator !=(const this_type &other) const
	{
		return !(*this == other);
	}

	bool operator <(const this_type &other) const
	{
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

	size_type offset() const
	{
		return sm->offset(pos);
	}

	pointer linearized_address() const
	{
		return arr+offset();
	}
};

template <typename T, typename SizeType>
inline
circular_buffer_iterator<T, SizeType> operator +(ptrdiff_t n, 
	const circular_buffer_iterator<T, SizeType> &x)
{
	return x+n;
}

template <typename T, typename SizeType = size_t>
struct circular_buffer_const_iterator {
	typedef T value_type;
	typedef const T *pointer;
	typedef const T &reference;
	typedef ptrdiff_t difference_type;
	typedef std::random_access_iterator_tag iterator_category;

	typedef circular_buffer_const_iterator<T, SizeType> this_type;
	typedef circular_buffer_iterator<T, SizeType> iterator;
	typedef SizeType size_type;
	typedef circular_buffer_base<size_type> space_manager_type;

	pointer arr;		// storage buffer
	space_manager_type *sm;	// space manager
	size_type pos;		// current position

	circular_buffer_const_iterator(): arr(NULL), sm(NULL), pos(0) {}

	explicit circular_buffer_const_iterator(pointer arr_, 
		space_manager_type *sm_, size_type pos_): arr(arr_), sm(sm_), pos(pos_) 
	{}

	circular_buffer_const_iterator(const iterator &iter): 
		arr(iter.arr), sm(iter.sm), pos(iter.pos)
	{}

	reference operator *() const { return arr[pos]; }

	pointer operator ->() const { return arr+pos; }

	reference operator [](difference_type n)
	{
		return arr[sm->advance(pos, n)];
	}

	this_type &operator ++()	// prefix increment
	{
		pos = sm->forward_n(pos, 1);
		return *this;
	}

	this_type operator ++(int)	// postfix increment
	{
		this_type temp(*this);
		pos = sm->forward_n(pos, 1);
		return temp;
	}

	this_type &operator --()	// prefix decrement
	{
		pos = sm->backward_n(pos, 1);
		return *this;
	}

	this_type operator --(int)	// postfix decrement
	{
		this_type temp(*this);
		pos = sm->backward_n(pos, 1);
		return temp;
	}

	this_type &operator +=(difference_type n)
	{
		pos = sm->advance(pos, n);
		return *this;
	}

	this_type &operator -=(difference_type n)
	{
		pos = sm->advance(pos, -n);
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
		return (this->linearized_address() - other.linearized_address());
	}

	bool operator ==(const this_type &other) const
	{
		return (arr == other.arr && sm == other.sm && pos == other.pos);
	}

	bool operator !=(const this_type &other) const
	{
		return !(*this == other);
	}

	bool operator <(const this_type &other) const
	{
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

	size_type offset() const
	{
		return sm->offset(pos);
	}

	pointer linearized_address() const
	{
		return arr+offset();
	}

	iterator to_iterator()
	{
		return iterator((T *) arr, sm, pos);
	}
};

template <typename T, typename SizeType>
inline
circular_buffer_const_iterator<T, SizeType> operator +(ptrdiff_t n, 
	const circular_buffer_const_iterator<T, SizeType> &x)
{
	return x+n;
}

template <typename T, typename SizeType>
inline
ptrdiff_t operator -(const circular_buffer_iterator<T, SizeType> &x, 
	const circular_buffer_const_iterator<T, SizeType> &y)
{
	return (x.linearized_address() - y.linearized_address());
}

template <typename T, typename SizeType>
inline
bool operator ==(const circular_buffer_iterator<T, SizeType> &x, 
	const circular_buffer_const_iterator<T, SizeType> &y)
{
	return (x.arr == y.arr && x.sm == y.sm && x.pos == y.pos);
}

template <typename T, typename SizeType>
inline
bool operator !=(const circular_buffer_iterator<T, SizeType> &x, 
	const circular_buffer_const_iterator<T, SizeType> &y)
{
	return !(x == y);
}

template <typename T, typename SizeType>
inline
bool operator <(const circular_buffer_iterator<T, SizeType> &x, 
	const circular_buffer_const_iterator<T, SizeType> &y)
{
	return (x.linearized_address() < y.linearized_address());
}

template <typename T, typename SizeType>
inline
bool operator >(const circular_buffer_iterator<T, SizeType> &x, 
	const circular_buffer_const_iterator<T, SizeType> &y)
{
	return !(x < y && x == y);
}

template <typename T, typename SizeType>
inline
bool operator <=(const circular_buffer_iterator<T, SizeType> &x, 
	const circular_buffer_const_iterator<T, SizeType> &y)
{
	return !(x > y);
}

template <typename T, typename SizeType>
inline
bool operator >=(const circular_buffer_iterator<T, SizeType> &x, 
	const circular_buffer_const_iterator<T, SizeType> &y)
{
	return !(x < y);
}

/* circular_buffer class */
template <typename T, typename Alloc = std::allocator<T>, 
	typename SizeType = size_t>
class circular_buffer: private Alloc {
public:
	/* Type Definitions of Vectors */
	typedef	T value_type;
	typedef Alloc allocator_type;
	typedef circular_buffer_iterator<T, SizeType> iterator;
	typedef circular_buffer_const_iterator<T, SizeType> const_iterator;

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
	typedef SizeType size_type;
#else // !( __cplusplus >= 201103L )
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef typename 
	std::iterator_traits<iterator>::difference_type difference_type;
	typedef SizeType size_type;
#endif // __cplusplus >= 201103L

	typedef std::pair<pointer, size_type> array_range;
	typedef std::pair<const_pointer, size_type> const_array_range;

private:
	typedef Hx::circular_buffer_base<size_type> space_manager_type;
	// member data
	pointer arr_;		// storage buffer
	space_manager_type sm_;	// storage manager
	
public:
	/**
	 * empty container constructor (default constructor)
	 * Constructs an empty container, with no elements.
	 */
	explicit circular_buffer(const allocator_type &alloc = allocator_type()):
		allocator_type(alloc) 
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
		const allocator_type &alloc = allocator_type()): allocator_type(alloc)
#else // !( __cplusplus >= 201103L ) 
	explicit circular_buffer(size_type n, const value_type &val = value_type(), 
		const allocator_type &alloc = allocator_type()): allocator_type(alloc)
#endif // __cplusplus >= 201103L
	{
		if (n == 0) {
			initialize();
			return;
		}

		initialize(n);

		try
		{
			uninitialized_fill_n(arr_, n, val);
			sm_.set_size(n);
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
		const allocator_type &alloc = allocator_type()): allocator_type(alloc)
#else // !( __cplusplus >= 201103L )
	template <typename InputIterator>
	circular_buffer(InputIterator first, InputIterator last,
		const allocator_type &alloc = allocator_type(), typename
		std::enable_if<!std::is_integral<InputIterator>::value>::type * = NULL):
		allocator_type(alloc)
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
			uninitialized_copy(first, last, arr_);
			sm_.set_size(n);
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
	circular_buffer(const circular_buffer &x): 
		allocator_type(*static_cast<const allocator_type *>(&x))
	{
		size_type n = x.size();
		if (n == 0) {
			initialize();
			return;
		}

		initialize(n);

		try
		{
			uninitialized_copy(x.begin(), x.end(), arr_);
			sm_.set_size(n);
		}
		catch (...)
		{
			finalize();
			throw;
		}
	}

	circular_buffer(const circular_buffer &x, const allocator_type &alloc): 
		allocator_type(alloc)
	{
		size_type n = x.size();
		if (n == 0) {
			initialize();
			return;
		}

		initialize(n);

		try
		{
			uninitialized_copy(x.begin(), x.end(), arr_);
			sm_.set_size(n);
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
		allocator_type(std::move(*static_cast<allocator_type *>(&x))),
		arr_(x.arr_), sm_(x.sm_)
	{
		x.initialize();
	}

	circular_buffer(circular_buffer &&x, const allocator_type &alloc): 
		allocator_type(alloc)
	{
		size_type n = x.size();
		if (n == 0) {
			initialize();
			return;
		}

		initialize(n);

		try
		{
			uninitialized_move(x.begin(), x.end(), arr_);
			sm_.set_size(n);
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

		this->clear();
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
		return make_iterator(sm_.front());
	}

	const_iterator begin() const noexcept
	{
		return make_const_iterator(sm_.front());
	}

	/**
	 * Return iterator to end
	 * Returns an iterator referring to the past-the-end element 
	 * in the circular_buffer container.
	 */
	iterator end() noexcept
	{
		return make_iterator(sm_.over_back());
	}

	const_iterator end() const noexcept
	{
		return make_const_iterator(sm_.over_back());
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
		return make_const_iterator(sm_.front());
	}

	/**
	 * Return const_iterator to end
	 * Returns a const_iterator pointing to the past-the-end element 
	 * in the container.
	 * The value returned shall not be dereferenced.
	 */
	const_iterator cend() const noexcept
	{
		return make_const_iterator(sm_.over_back());
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
		return sm_.size();
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
		return sm_.capacity();
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
		sm_.set_size(n);
	}

	/**
	 * Test whether container is empty
	 * Returns whether the circular_buffer container is empty 
	 * (i.e. whether its size is 0).
	 */
	bool empty() const noexcept { return sm_.is_empty(); }

	/**
	 * Test whether circular_buffer is full
	 * Returns whether the circular_buffer is full 
	 * (i.e. whether its size is its capacity).
	 * This function does not modify the container in any way. 
	 */
	bool full() const noexcept
	{
		return sm_.is_full();
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
		size_type old_size = size();

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

		arr_ = new_array;
		sm_ = space_manager_type(n);
		sm_.set_size(old_size);
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
		circular_buffer x(std::move(*this), *static_cast<allocator_type *>(this));
#else // !( __cplusplus >= 201103L )
		circular_buffer x(*this, *static_cast<allocator_type *>(this));
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
		return arr_[sm_.advance(sm_.front(), n)];
	}

	const_reference operator [](size_type n) const 
	{
		return arr_[sm_.advance(sm_.front(), n)];
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
	reference front() { return arr_[sm_.front()]; }

	const_reference front() const { return arr_[sm_.front()]; }

	/**
	 * Access last element
	 * Returns a reference to the last element in the container.
	 */
	reference back()
	{
		return arr_[sm_.back()];
	}

	const_reference back() const
	{
		return arr_[sm_.back()];
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
			circular_buffer x(first, last, *static_cast<allocator_type *>(this));
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
		sm_.set_size(n);
	}

	/**
	 * In the fill version, the new contents are n elements, 
	 * each initialized to a copy of val.
	 */
	void assign(size_type n, const value_type &val)
	{
		if (n > capacity()) {
			circular_buffer x(n, val, *static_cast<allocator_type *>(this));
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
		sm_.set_size(n);
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

		construct(&arr_[sm_.over_back()], val);
		sm_.push_back();
	}

#if __cplusplus >= 201103L
	void push_back(value_type &&val)
	{
		if (full()) {
			reserve(adjust_capacity());
		}

		construct(&arr_[sm_.over_back()], std::forward<value_type>(val));
		sm_.push_back();
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

		construct(&arr_[sm_.under_front()], val);
		sm_.push_front();
	}

#if __cplusplus >= 201103L
	void push_front(value_type &&val)
	{
		if (full()) {
			reserve(adjust_capacity());
		}

		construct(&arr_[sm_.under_front()], std::forward<value_type>(val));
		sm_.push_front();
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
		destroy(&arr_[sm_.back()]);
		sm_.pop_back();
	}

	/**
	 * Delete first element
	 * Removes the first element in the circular_buffer container, 
	 * effectively reducing its size by one.
	 */
	void pop_front()
	{
		assert(!empty());
		destroy(&arr_[sm_.front()]);
		sm_.pop_front();
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
			size_type idx = position.offset();
			reserve(adjust_capacity());
			position = make_const_iterator(idx);
		}

		iterator pos = position.to_iterator();
		if (position.offset() <= size()/2) { // vacate front
			if (pos == begin() || vacate_front(pos, n)) {
				uninitialized_fill_n(pos-n, n, val);
			} else {
				std::fill_n(pos-n, n, val);
			}
			sm_.push_front_n(n);
			return pos-n;
		} else {	// vacate back
			if (pos == end() || vacate_back(pos, n)) {
				uninitialized_fill_n(pos, n, val);
			} else {
				std::fill_n(pos, n, val);
			}
			sm_.push_back_n(n);
			return pos;
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

		size_type n = std::distance(first, last);

		if (n == 0)
			return position.to_iterator();

		if (capacity() < size()+n) {	// need reallocate
			size_type idx = position.offset();
			reserve(adjust_capacity());
			position = make_const_iterator(idx);
		}

		iterator pos = position.to_iterator();
		if (position.offset() <= size()/2) { // vacate front
			if (pos == begin() || vacate_front(pos, n)) {
				uninitialized_copy(first, last, pos-n);
			} else {
				std::copy(first, last, pos-n);
			}
			sm_.push_front_n(n);
			return pos-n;
		} else {	// vacate back
			if (pos == end() || vacate_back(pos, n)) {
				uninitialized_copy(first, last, pos);
			} else {
				std::copy(first, last, pos);
			}
			sm_.push_back_n(n);
			return pos;
		}
	}
	
#if __cplusplus >= 201103L
	iterator insert(const_iterator position, value_type &&val)
	{
		assert(position <= end()); 

		if (full()) {	// need reallocate
			size_type idx = position.offset();
			reserve(adjust_capacity());
			position = make_const_iterator(idx);
		}

		iterator pos = position.to_iterator();
		if (position.offset() <= size()/2) { // vacate front
			if (pos == begin() || vacate_front(pos, 1)) {
				construct(pos-1, std::move(val));
			} else {
				*(pos-1) = std::move(val);
			}
			sm_.push_front();
			return pos-1;
		} else {	// vacate back
			if (pos == end() || vacate_back(pos, 1)) {
				construct(pos, std::move(val));
			} else {
				*pos = std::move(val);
			}
			sm_.push_back();
			return pos;
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
			sm_.pop_front();
		} else {	// move from back
			iterator pos = position.to_iterator();
			iterator finish = end();
#if __cplusplus >= 201103L
			std::move(pos+1, finish, pos);
#else // !( __cplusplus >= 201103L )
			std::copy(pos+1, finish, pos);
#endif // __cplusplus >= 201103L
			destroy(finish-1);
			sm_.pop_back();
		}
		return position.to_iterator();
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
			size_type n = range_destroy(start, iter);
			sm_.pop_front_n(n);
		} else {	// move from back
			iterator finish = end();
#if __cplusplus >= 201103L
			iterator iter = std::move(last.to_iterator(), finish, 
				first.to_iterator());
#else // !( __cplusplus >= 201103L )
			iterator iter = std::copy(last.to_iterator(), finish, 
				first.to_iterator());
#endif // __cplusplus >= 201103L
			size_type n = range_destroy(iter, finish);
			sm_.pop_back_n(n);
		}
		return first.to_iterator();
	}

	/**
	 * Swap content
	 * Exchanges the content of the container by the content of x, 
	 * which is another circular_buffer object of the same type.
	 */
	void swap(circular_buffer &x)
	{
		using std::swap;

		swap(*static_cast<allocator_type *>(this), 
			*static_cast<allocator_type *>(&x));
		this->swap_data(x);
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
		sm_.set_size(0);
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
			size_type idx = position.offset();
			reserve(adjust_capacity());
			position = make_const_iterator(idx);
		}

		iterator pos = position.to_iterator();
		if (position.offset() <= size()/2) { // vacate front
			if (pos == begin() || vacate_front(pos, 1)) {
				construct(pos-1, std::forward<Args>(args) ...);
			} else {
				*(pos-1) = value_type(std::forward<Args>(args) ...);
			}
			sm_.push_front();
			return pos-1;
		} else {	// vacate back
			if (pos == end() || vacate_back(pos, 1)) {
				construct(pos, std::forward<Args>(args) ...);
			} else {
				*pos = value_type(std::forward<Args>(args) ...);
			}
			sm_.push_back();
			return pos;
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

		construct(&arr_[sm_.under_front()], std::forward<Args>(args) ...);
		sm_.push_front();
	}

	template <typename ... Args>
	void emplace_back(Args &&... args)
	{
		if (full()) {
			reserve(adjust_capacity());
		}

		construct(&arr_[sm_.over_back()], std::forward<Args>(args) ...);
		sm_.push_back();
	}
#endif // __cplusplus >= 201103L

	/**
	 * Get allocator
	 * Returns a copy of the allocator object associated with 
	 * the circular_buffer.
	 */
	allocator_type get_allocator() const noexcept
	{
		return *this;
	}

public:
	bool is_linearized() const { return sm_.is_linearized(); }

	pointer linearize()
	{
		if (!is_linearized()) {
#if __cplusplus >= 201103L
			circular_buffer x(std::move(*this), 
				*static_cast<allocator_type *>(this));
#else // !( __cplusplus >= 201103L )
			circular_buffer x(*this, *static_cast<allocator_type *>(this));
#endif // __cplusplus >= 201103L
			this->swap_data(x);
		}
		return &arr_[sm_.front()];
	}

	array_range array_one()
	{
		if (is_linearized()) {
			return array_range(&arr_[sm_.front()], sm_.size());
		} else {
			return array_range(&arr_[sm_.front()], sm_.array_one_size());
		}
	}

	const_array_range array_one() const 
	{
		if (is_linearized()) {
			return const_array_range(&arr_[sm_.front()], sm_.size());
		} else {
			return const_array_range(&arr_[sm_.front()], sm_.array_one_size());
		}
	}

	array_range array_two()
	{
		if (is_linearized()) {
			return array_range(&arr_[sm_.over_back()], 0);
		} else {
			return array_range(arr_, sm_.array_two_size());
		}
	}

	const_array_range array_two() const 
	{
		if (is_linearized()) {
			return const_array_range(&arr_[sm_.over_back()], 0);
		} else {
			return const_array_range(arr_, sm_.array_two_size());
		}
	}

private:
	size_type adjust_capacity(size_type hint = 0)
	{
		if (hint < 3) hint = 3;
		return std::max(hint, 2*capacity()+1);
	}

	void swap_data(circular_buffer &x)
	{
		std::swap(arr_, x.arr_);
		std::swap(sm_, x.sm_);
	}

	iterator make_iterator(size_type pos) {
		return iterator(arr_, &sm_, pos);
	}

	const_iterator make_const_iterator(size_type pos) const {
		return const_iterator(arr_, (space_manager_type *) &sm_, pos);
	}

	/**
	 * vacate n element's space from head for insert before pos.
	 * if uninitialized buffer, return true, otherwise return false
	 */
#if __cplusplus >= 201103L
	bool vacate_front(iterator pos, size_type n)
	{
		iterator start = begin();
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
	bool vacate_front(iterator pos, size_type n)
	{
		iterator start = begin();
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
	bool vacate_back(iterator pos, size_type n)
	{
		iterator finish = end();
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
	bool vacate_back(iterator pos, size_type n)
	{
		iterator finish = end();
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
		return std::allocator_traits<allocator_type>::allocate(
			*static_cast<allocator_type *>(this), n);
#else // !( __cplusplus >= 201103L )
		return static_cast<allocator_type *>(this)->allocate(n);
#endif // __cplusplus >= 201103L
	}

	void deallocate(pointer p, size_type n)
	{
		if (p == NULL || n == 0)
			return;

#if __cplusplus >= 201103L
		std::allocator_traits<allocator_type>::deallocate(
			*static_cast<allocator_type *>(this), p, n);
#else // !( __cplusplus >= 201103L )
		return static_cast<allocator_type *>(this)->deallocate(p, n);
#endif // __cplusplus >= 201103L
	}

#if __cplusplus >= 201103L
	template <typename ...Args>
	void construct(pointer p, Args &&...args)
	{
		std::allocator_traits<allocator_type>::construct(
			*static_cast<allocator_type *>(this), p, 
			std::forward<Args>(args)...);
	}

	template <typename ...Args>
	void construct(iterator iter, Args &&...args)
	{
		construct(iter.arr+iter.pos, std::forward<Args>(args)...);
	}
#else // !( __cplusplus >= 201103L )
	void construct(pointer p, const value_type &val)
	{
		static_cast<allocator_type *>(this)->construct(p, val);
	}

	void construct(iterator iter, const value_type &val) 
	{
		construct(iter.arr+iter.pos, val);
	}
#endif // __cplusplus >= 201103L

	void destroy(pointer p)
	{
#if __cplusplus >= 201103L
		std::allocator_traits<allocator_type>::destroy(
			*static_cast<allocator_type *>(this), p);
#else // !( __cplusplus >= 201103L )
		static_cast<allocator_type *>(this)->destroy(p);
#endif // __cplusplus >= 201103L
	}

	void destroy(iterator iter)
	{
		destroy(iter.arr+iter.pos);
	}

	size_type range_destroy(pointer first, pointer last)
	{
		size_type n = 0;
		while (last != first) {
			destroy(--last);
			n++;
		}
		return n;
	}

	size_type range_destroy(iterator first, iterator last)
	{
		size_type n = 0;
		while (last != first) {
			destroy(--last);
			n++;
		}
		return n;
	}

	void initialize()
	{
		arr_ = NULL;
		sm_ = space_manager_type();
	}

	void initialize(size_type n)
	{
		arr_ = allocate(n+1);
		sm_= space_manager_type(n);
	}

	void finalize()
	{
		range_destroy(begin(), end());
		deallocate(arr_, sm_.capacity()+1);
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

}	// namespace opt

}	// namespace Hx

#endif // HX_OPT_CIRCULAR_BUFFER_H

