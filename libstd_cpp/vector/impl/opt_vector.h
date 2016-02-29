// -*- C++ -*-
// HeXu's
// 2013 Aug

#ifndef HX_OPT_VECTOR_H
#define HX_OPT_VECTOR_H

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

#include "vector_base.h"

namespace Hx {

// optional
namespace opt {

/* vector class */
template <typename T, typename Alloc = std::allocator<T>, 
	typename SizeType = size_t>
class vector: private Alloc {
public:
	/* Type Definitions of Vectors */
	typedef	T value_type;
	typedef Alloc allocator_type;

#if __cplusplus >= 201103L
	typedef T &reference;
	typedef const T &const_reference;
	typedef typename std::allocator_traits<allocator_type>::pointer pointer;
	typedef typename std::allocator_traits<allocator_type>::const_pointer const_pointer;
	typedef pointer iterator;
	typedef const_pointer const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef typename std::iterator_traits<iterator>::difference_type difference_type;
	typedef SizeType size_type;
#else // !( __cplusplus >= 201103L )
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef pointer iterator;
	typedef const_pointer const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef typename std::iterator_traits<iterator>::difference_type difference_type;
	typedef SizeType size_type;
#endif // __cplusplus >= 201103L

private:
	typedef Hx::vector_base<size_type> space_manager_type;
	// member data
	pointer arr_;	// pointer to data
	space_manager_type sm_;	// space manager
	
public:
	/**
	 * Construct vector
	 * Constructs a vector, 
	 * initializing its contents depending on the constructor version used:
	 */

	/** 
	 * empty container constructor (default constructor)
	 * Constructs an empty container, with no elements.
	 */
	explicit vector(const allocator_type &alloc = allocator_type()):
		allocator_type(alloc)
	{
		initialize();
	} 

	/**
	 * fill constructor
	 * Constructs a container with n elements. Each element is a copy of val.
	 */
#if __cplusplus >= 201103L
	explicit vector(size_type n): vector(n, value_type(), allocator_type()) {}
#endif // __cplusplus >= 201103L

#if __cplusplus >= 201103L
	vector(size_type n, const value_type &val, 
		const allocator_type &alloc = allocator_type()): allocator_type(alloc)
#else // !( __cplusplus >= 201103L ) 
	explicit vector(size_type n, const value_type &val = value_type(), 
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
			uninitialized_fill_n(begin(), n, val);
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
	vector(InputIterator first, InputIterator last,
		const allocator_type &alloc = allocator_type()): allocator_type(alloc)
#else // !( __cplusplus >= 201103L )
	template <typename InputIterator>
	vector(InputIterator first, InputIterator last,
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
			uninitialized_copy(first, last, begin());
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
	vector(const vector &x): 
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
			uninitialized_copy(x.begin(), x.end(), begin());
			sm_.set_size(n);
		}
		catch (...)
		{
			finalize();
			throw;
		}
	}

	vector(const vector &x, const allocator_type &alloc): allocator_type(alloc)
	{
		size_type n = x.size();
		if (n == 0) {
			initialize();
			return;
		}

		initialize(n);

		try
		{
			uninitialized_copy(x.begin(), x.end(), begin());
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
	vector(vector &&x): 
		allocator_type(std::move(*static_cast<allocator_type *>(&x))),
		arr_(x.arr_), sm_(x.sm_)
	{
		x.initialize();
	}

	vector(vector &&x, const allocator_type &alloc): allocator_type(alloc)
	{
		size_type n = x.size();
		if (n == 0) {
			initialize();
			return;
		}

		initialize(n);

		try
		{
			uninitialized_move(x.begin(), x.end(), begin());
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
	vector(std::initializer_list<value_type> il,
		const allocator_type &alloc = allocator_type()): 
		vector(il.begin(), il.end(), alloc) {}
#endif // __cplusplus >= 201103L

	/**
	 * Vector destructor
	 * Destroys the container object.
	 */
	~vector() { finalize(); }

	/**
	 * The copy assignment 
	 * copies all the elements from x into the container 
	 * (with x preserving its contents).
	 */
	vector &operator =(const vector &x)
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
	vector &operator =(vector &&x)
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
	vector &operator =(std::initializer_list<value_type> il)
	{
		assign(il.begin(), il.end());
		return *this;
	}
#endif // __cplusplus >= 201103L

	/**
	 * Return iterator to beginning
	 * Returns an iterator pointing to the first element in the vector.
	 */
	iterator begin() noexcept { return arr_; }
	const_iterator begin() const noexcept { return arr_; }

	/**
	 * Return iterator to end
	 * Returns an iterator referring to the past-the-end element 
	 * in the vector container.
	 */
	iterator end() noexcept { return arr_+sm_.over_back(); }
	const_iterator end() const noexcept { return arr_+sm_.over_back(); }

	/**
	 * Return reverse iterator to reverse beginning
	 * Returns a reverse iterator pointing to the last element in the vector 
	 * (i.e., its reverse beginning).
	 */
	reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

	const_reverse_iterator rbegin() const noexcept 
	{
		return const_reverse_iterator(end()); 
	}

	/**
	 * Return reverse iterator to reverse end
	 * Returns a reverse iterator pointing to the theoretical element preceding 
	 * the first element in the vector (which is considered its reverse end).
	 */
	reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

	const_reverse_iterator rend() const noexcept 
	{
		return const_reverse_iterator(begin()); 
	}

	/**
	 * Return const_iterator to beginning
	 * Returns a const_iterator pointing to the first element in the container.
	 */
	const_iterator cbegin() const noexcept { return begin(); }

	/**
	 * Return const_iterator to end
	 * Returns a const_iterator pointing to the past-the-end element 
	 * in the container.
	 * The value returned shall not be dereferenced.
	 */
	const_iterator cend() const noexcept { return end(); }

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
	 * Returns the number of elements in the vector.
	 * This is the number of actual objects held in the vector, 
	 * which is not necessarily equal to its storage capacity.
	 */
	size_type size() const noexcept { return sm_.size(); }

	/**
	 * Return maximum size
	 * Returns the maximum number of elements that the vector can hold.
	 */
	size_type max_size() const noexcept
	{
		return std::numeric_limits<size_type>::max();
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
	 * Return size of allocated storage capacity
	 * Returns the size of the storage space currently allocated 
	 * for the vector, expressed in terms of elements.
	 */
	size_type capacity() const noexcept { return sm_.capacity(); }

	/**
	 * Test whether vector is empty
	 * Returns whether the vector is empty (i.e. whether its size is 0).
	 * This function does not modify the container in any way. 
	 */
	bool empty() const { return sm_.is_empty(); }

	/**
	 * Test whether vector is full
	 * Returns whether the vector is full 
	 * (i.e. whether its size is its capacity).
	 * This function does not modify the container in any way. 
	 */
	bool full() const { return sm_.is_full(); }

	/**
	 * Request a change in capacity
	 * Requests that the vector capacity be at least enough 
	 * to contain n elements.
	 */
	void reserve(size_type n)
	{
		if (n <= capacity()) return;

		// allocate newbuf and remember oldbuf, oldbuf's size and capacity
		pointer new_arr = allocate(n);

		// copy from oldbuf to newbuf and set newbuf's size and capacity
		try
		{
#if __cplusplus >= 201103L
			uninitialized_move(begin(), end(), new_arr);
#else // !( __cplusplus >= 201103L )
			uninitialized_copy(begin(), end(), new_arr);
#endif // __cplusplus >= 201103L
		}
		catch (...)
		{
			deallocate(new_arr, n);
			throw;
		}
		finalize();
		arr_ = new_arr;
		sm_.set_capacity(n);
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
		vector x(std::move(*this), *static_cast<allocator_type *>(this));
#else // !( __cplusplus >= 201103L )
		vector x(*this, *static_cast<allocator_type *>(this));
#endif // __cplusplus >= 201103L
		this->swap_data(x);
	}

	/**
	 * Access element
	 * Returns a reference to the element at position n in the vector container.
	 */
	reference operator [](size_type n) { return arr_[n]; }

	const_reference operator [](size_type n) const { return arr_[n]; }
	
	/**
	 * Access element
	 * Returns a reference to the element at position n in the vector.
	 */
	reference at(size_type n)
	{
		if (n >= size())
			throw std::out_of_range(__func__);
		return arr_[n];
	}

	const_reference at(size_type n) const
	{
		if (n >= size())
			throw std::out_of_range(__func__);
		return arr_[n];
	}
	
	/**
	 * Access first element
	 * Returns a reference to the first element in the vector.
	 */
	reference front() 
	{
		assert(!empty());
		return arr_[0];
	}

	const_reference front() const 
	{
		assert(!empty());
		return arr_[0];
	}

	/**
	 * Access last element
	 * Returns a reference to the last element in the vector.
	 */
	reference back() 
	{
		assert(!empty());
		return arr_[sm_.back()];
	}

	const_reference back() const 
	{
		assert(!empty());
		return arr_[sm_.back()];
	}

	/**
	 * Access data
	 * Returns a direct pointer to the memory array used internally by 
	 * the vector to store its owned elements.
	 */
	value_type *data() noexcept { return arr_; }
	const value_type *data() const noexcept { return arr_; }

	/**
	 * Assign vector content
	 * Assigns new contents to the vector, replacing its current contents, 
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
			vector x(first, last, *static_cast<allocator_type *>(this));
			this->swap_data(x);
			return;
		}

		// assign elements
		size_type sz = size();
		std::copy_n(first, std::min(n, sz), begin());

		if (sz < n) {	// this->size() < std::distance(first, last)
			std::advance(first, sz);
			uninitialized_copy(first, last, end());
		} else {	// this->size() >= std::distance(first, last)
			range_destroy(begin()+n, end());
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
			vector x(n, val, *static_cast<allocator_type *>(this));
			this->swap_data(x);
			return;
		}

		// assign elements
		size_type sz = size();
		std::fill_n(begin(), std::min(n, sz), val);

		if (sz < n) {	// this->size() < std::distance(first, last)
			uninitialized_fill(begin()+sz, begin()+n, val);
		} else if (sz > n) {	// this->size() > std::distance(first, last)
			range_destroy(begin()+n, end());
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
	 * Adds a new element at the end of the vector, after its current last 
	 * element. The content of val is copied (or moved) to the new element.
	 */
	void push_back(const value_type &val)
	{
		if (full()) {
			reserve(adjust_capacity());
		}

		construct(end(), val);
		sm_.push_back();
	}

#if __cplusplus >= 201103L
	void push_back(value_type &&val)
	{
		if (full()) {
			reserve(adjust_capacity());
		}

		construct(end(), std::forward<value_type>(val));
		sm_.push_back();
	}
#endif // __cplusplus >= 201103L

	/**
	 * Delete last element
	 * Removes the last element in the vector, effectively reducing 
	 * the container size by one.
	 */
	void pop_back()
	{
		assert(!empty());
		destroy(end()-1);
		sm_.pop_back();
	}

	/**
	 * Insert elements
	 * The vector is extended by inserting new elements before the element 
	 * at the specified position, effectively increasing the container size 
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
			return (iterator) position;

		if (capacity() < size()+n) {	// need reallocate
			size_type idx = position-begin();
			reserve(adjust_capacity(size()+n));
			position = begin()+idx;
		}

		iterator pos = (iterator) position;
		if (pos == end() || vacate(pos, n)) {
			uninitialized_fill_n(pos, n, val);
		} else {
			std::fill_n(pos, n, val);
		}
		sm_.push_back_n(n);
		return pos;
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
			return (iterator) position;

		if (capacity() < size()+n) {	// need reallocate
			size_type idx = position-begin();
			reserve(size()+n);
			position = begin()+idx;
		}

		iterator pos = (iterator) position;
		if (pos == end() || vacate(pos, n)) {
			uninitialized_copy(first, last, pos);
		} else {
			std::copy(first, last, pos);
		}
		sm_.push_back_n(n);
		return pos;
	}
	
#if __cplusplus >= 201103L
	iterator insert(const_iterator position, value_type &&val)
	{
		if (full()) {	// need reallocate
			size_type idx = position-begin();
			reserve(adjust_capacity());
			position = begin()+idx;
		}

		iterator pos = (iterator) position;
		if (pos == end() || vacate(pos, 1)) {
			construct(pos, std::move(val));
		} else {
			*pos = std::move(val);
		}
		sm_.push_back();
		return pos;
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
	 * Removes from the vector either a single element (position) 
	 * or a range of elements ([first,last)).
	 */
	iterator erase(const_iterator position)
	{
		assert(!empty() && position <= end());

		if (position == end()) return end();

#if __cplusplus >= 201103L
		std::move((iterator) position+1, end(), (iterator) position);
#else // !( __cplusplus >= 201103L )
		std::copy((iterator) position+1, end(), (iterator) position);
#endif // __cplusplus >= 201103L
		destroy(end()-1);
		sm_.pop_back();
		return (iterator) position;
	}

	iterator erase(const_iterator first, const_iterator last)
	{
		assert(!empty() && first <= last);

		if (first == last) 
			return (iterator) first;

#if __cplusplus >= 201103L
		iterator iter = std::move((iterator) last, end(), (iterator) first);
#else // !( __cplusplus >= 201103L )
		iterator iter = std::copy((iterator) last, end(), (iterator) first);
#endif // __cplusplus >= 201103L
		size_type n = range_destroy(iter, end());
		sm_.pop_back_n(n);
		return (iterator) first;
	}

	/**
	 * Swap content
	 * Exchanges the content of the container by the content of x, 
	 * which is another vector object of the same type. Sizes may differ.
	 */
	void swap(vector &x)
	{
		using std::swap;

		swap(*static_cast<allocator_type *>(this), 
			*static_cast<allocator_type *>(&x));
		this->swap_data(x);
	}

	/**
	 * Clear content
	 * Removes all elements from the vector (which are destroyed), 
	 * leaving the container with a size of 0.
	 */
	void clear() noexcept
	{
		range_destroy(begin(), end());
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
		if (full()) {	// need reallocate
			size_type off = position-begin();
			reserve(adjust_capacity());
			position = begin()+off;
		}

		iterator pos = (iterator) position;
		if (pos == end() || vacate(pos, 1)) {
			construct(end(), std::forward<Args>(args) ...);
		} else {
			*pos = value_type(std::forward<Args>(args) ...);
		}
		sm_.push_back();
		return pos;
	}

	/**
	 * Construct and insert element at the end
	 * Inserts a new element at the end of the vector, right after its 
	 * current last element. This new element is constructed in place 
	 * using args as the arguments for its constructoe.
	 */
	template <typename ... Args>
	void emplace_back(Args &&... args)
	{
		if (full()) {
			reserve(adjust_capacity());
		}

		construct(end(), std::forward<Args>(args) ...);
		sm_.push_back();
	}
#endif // __cplusplus >= 201103L

	/**
	 * Get allocator
	 * Returns a copy of the allocator object associated with the vector.
	 */
	allocator_type get_allocator() const noexcept
	{
		return *this;
	}

private:
	size_type adjust_capacity(size_type hint = 0)
	{
		if (hint < 4) hint = 4;
		return std::max<size_type>(hint, 2*capacity());
	}

	void swap_data(vector &x)
	{
		std::swap(arr_, x.arr_);
		std::swap(sm_, x.sm_);
	}

	/**
	 * vacate n element's space for insert before pos.
	 * if uninitialized buffer, return true, otherwise return false
	 */
#if __cplusplus >= 201103L
	bool vacate(iterator pos, size_type n)
	{
		iterator finish = end();
		if (finish-pos <= n) {
			uninitialized_move(pos, finish, pos+n);
			range_destroy(pos, finish);
			return true;
		} else {	// finish_-pos > n
			uninitialized_move_n(finish-n, n, finish);
			std::move_backward(pos, finish-n, finish);
			return false;
		}
	}
#else // !( __cplusplus >= 201103L )
	bool vacate(iterator pos, size_type n)
	{
		iterator finish = end();
		if (finish-pos <= n) {
			uninitialized_copy(pos, finish, pos+n);
			range_destroy(pos, finish);
			return true;
		} else {	// finish_-pos > n
			uninitialized_copy_n(finish-n, n, finish);
			std::copy_backward(pos, finish-n, finish);
			return false;
		}
	}
#endif // __cplusplus >= 201103L

	pointer allocate(size_type n)
	{
		if (n == 0)
			return NULL;

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
#else // !( __cplusplus >= 201103L )
	void construct(pointer p, const value_type &val)
	{
		static_cast<allocator_type *>(this)->construct(p, val);
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

	size_type range_destroy(pointer first, pointer last)
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
		arr_ = allocate(n);
		sm_= space_manager_type(n);
	}

	void finalize()
	{
		range_destroy(begin(), end());
		deallocate(begin(), capacity());
	}

	template <typename InputIterator>
	iterator uninitialized_copy(InputIterator first, InputIterator last,
		iterator result)
	{
		iterator save(result);
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
	template <typename InputIterator>
	iterator uninitialized_move(InputIterator first, InputIterator last,
		iterator result)
	{
		iterator save(result);
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

	template <typename InputIterator>
	iterator uninitialized_copy_n(InputIterator first, size_type n, 
		iterator result)
	{
		iterator save(result);
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
	template <typename InputIterator>
	iterator uninitialized_move_n(InputIterator first, size_type n, 
		iterator result)
	{
		iterator save(result);
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

	void uninitialized_fill(iterator first, iterator last, const value_type &x)
	{
		iterator save(first);
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

	iterator uninitialized_fill_n(iterator first, size_type n, 
		const value_type &x)
	{
		iterator save(first);
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
 * Relational operators for vector
 * Performs the appropriate comparison operation between the vector containers 
 * lhs and rhs.
 */
template <typename T, typename Alloc>
bool operator ==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	if (lhs.size() != rhs.size())
		return false;

	return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T, typename Alloc>
inline
bool operator !=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return !(lhs == rhs);
}

template <typename T, typename Alloc>
bool operator <(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return std::lexicographical_compare(lhs.begin(), lhs.end(),
		rhs.begin(), rhs.end());
}

template <typename T, typename Alloc>
bool operator >(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return (rhs < lhs);
}

template <typename T, typename Alloc>
bool operator <=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return !(lhs > rhs);
}

template <typename T, typename Alloc>
bool operator >=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return !(lhs < rhs);
}

/**
 * Exchange contents of vectors
 * The contents of container x are exchanged with those of y. 
 * Both container objects must be of the same type (same template parameters), 
 * although sizes may differ.
 */
template <typename T, typename Alloc>
inline
void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
{
	return x.swap(y);
}

}	// namespace opt

}	// namespace Hx

#endif // HX_OPT_VECTOR_H

