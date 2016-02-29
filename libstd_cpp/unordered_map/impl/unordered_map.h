// -*- C++ -*-
// HeXu's
// 2013 Dec

#ifndef HX_UNORDERED_MAP_H
#define HX_UNORDERED_MAP_H

#include <cassert>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <memory>
#include <limits>
#include <algorithm>

#if __cplusplus >= 201103L
#include <initializer_list>
#endif // __cplusplus >= 201103L

#include "key_words.h"
#include "type_traits.h"
#include "functional.h"
#include "slist_impl.h"

namespace Hx {

/**
 * A helper node class for unordered_map.
 * This is just a linked list with uninitialized storage for a
 * data value in each node.
 */
template <typename T>
struct unordered_map_node: public detail::slist_node_t {
	// raw storage buffer for type T
	typename 
	std::aligned_storage<sizeof (T), std::alignment_of<T>::value>::type storage;

	T *valptr() noexcept
	{
		return static_cast<T *>(static_cast<void *>(&storage));
	}

	const T *valptr() const noexcept
	{
		return static_cast<const T *>(static_cast<const void *>(&storage));
	}
};

/**
 * A unordered_map::local_iterator.
 * All the functions are op overloads.
 */
template <typename T>
struct unordered_map_local_iterator {
	typedef T value_type;
	typedef T *pointer;
	typedef T &reference;
	typedef ptrdiff_t difference_type;
	typedef std::forward_iterator_tag iterator_category;

	typedef unordered_map_local_iterator<T> this_type;
	typedef unordered_map_node<T> node_type;

	typedef detail::slist_node_t link_type;
	link_type *link;

	unordered_map_local_iterator(): link(NULL) {}

	explicit unordered_map_local_iterator(link_type *link_): link(link_) {}

	reference operator *() const
	{
		return *static_cast<node_type *>(link)->valptr();
	}

	pointer operator ->() const
	{
		return static_cast<node_type *>(link)->valptr();
	}

	this_type &operator ++()
	{
		next();
		return *this;
	}

	this_type operator ++(int)
	{
		this_type tmp(*this);
		next();
		return tmp;
	}

	bool operator ==(const this_type &other) const
	{
		return (this->link == other.link);
	}

	bool operator !=(const this_type &other) const
	{
		return !(*this == other);
	}

	void next()
	{
		link = link->next;
	}
};

/**
 * A unordered_map::const_local_iterator.
 * All the functions are op overloads.
 */
template <typename T>
struct unordered_map_const_local_iterator {
	typedef T value_type;
	typedef const T *pointer;
	typedef const T &reference;
	typedef ptrdiff_t difference_type;
	typedef std::forward_iterator_tag iterator_category;

	typedef unordered_map_const_local_iterator<T> this_type;
	typedef const unordered_map_node<T> node_type;
	typedef unordered_map_local_iterator<T> local_iterator;

	typedef detail::slist_node_t link_type;
	const link_type *link;

	unordered_map_const_local_iterator(): link(NULL) {}

	explicit unordered_map_const_local_iterator(const link_type *link_): 
		link(link_) {}

	unordered_map_const_local_iterator(const local_iterator &iter): 
		link(iter.link) {}

	reference operator *() const
	{
		return *static_cast<node_type *>(link)->valptr();
	}

	pointer operator ->() const
	{
		return static_cast<node_type *>(link)->valptr();
	}

	this_type &operator ++()
	{
		next();
		return *this;
	}

	this_type operator ++(int)
	{
		this_type temp(*this);
		next();
		return temp;
	}

	bool operator ==(const this_type &other) const
	{
		return (this->link == other.link);
	}

	bool operator !=(const this_type &other) const
	{
		return !(*this == other);
	}

	void next()
	{
		link = link->next;
	}
};

/**
 * Unordered map local iterator equality comparison.
 */
template <typename T>
inline 
bool operator ==(const unordered_map_local_iterator<T> &x,
	const unordered_map_const_local_iterator<T> &y)
{
	return (x.link == y.link);
}

/**
 * Unordered map local iterator inequality comparison.
 */
template <typename T>
inline 
bool operator !=(const unordered_map_local_iterator<T> &x,
	const unordered_map_const_local_iterator<T> &y)
{
	return !(x == y);
}

/**
 * A unordered_map::iterator.
 * All the functions are op overloads.
 */
template <typename T>
struct unordered_map_iterator {
	typedef T value_type;
	typedef T *pointer;
	typedef T &reference;
	typedef ptrdiff_t difference_type;
	typedef std::forward_iterator_tag iterator_category;

	typedef unordered_map_iterator<T> this_type;
	typedef unordered_map_node<T> node_type;

	typedef detail::slist_t bucket_type;
	typedef detail::slist_node_t link_type;
	bucket_type *pos;
	bucket_type *end;
	link_type *link;

	unordered_map_iterator(): pos(NULL), end(NULL), link(NULL) {}

	unordered_map_iterator(bucket_type *pos_, bucket_type *end_, 
		link_type *link_): pos(pos_), end(end_), link(link_) 
	{}

	reference operator *() const
	{
		return *static_cast<node_type *>(link)->valptr();
	}

	pointer operator ->() const
	{
		return static_cast<node_type *>(link)->valptr();
	}

	this_type &operator ++()
	{
		next();
		return *this;
	}

	this_type operator ++(int)
	{
		this_type tmp(*this);
		next();
		return tmp;
	}

	bool operator ==(const this_type &other) const
	{
		return (this->pos == other.pos) && (this->link == other.link);
	}

	bool operator !=(const this_type &other) const
	{
		return !(*this == other);
	}

	void next()
	{
		// get current bucket next
		link = link->next;

		// reach current bucket end
		if (link == NULL) {
			assert(pos != end);	// if this is end, next is undefined
			// search next non-empty bucket
			for (pos += 1; pos != end && slist_is_empty(pos); ++pos)
				;
			if (pos == end) {	// get bucket end
				link = NULL;
			} else {	// get an non-empty bucket
				link = pos->head.next;
			}
		}
	}
};

/**
 * A unordered_map::const_iterator.
 * All the functions are op overloads.
 */
template <typename T>
struct unordered_map_const_iterator {
	typedef T value_type;
	typedef const T *pointer;
	typedef const T &reference;
	typedef ptrdiff_t difference_type;
	typedef std::forward_iterator_tag iterator_category;

	typedef unordered_map_const_iterator<T> this_type;
	typedef const unordered_map_node<T> node_type;
	typedef unordered_map_iterator<T> iterator;

	typedef const detail::slist_t bucket_type;
	typedef const detail::slist_node_t link_type;
	bucket_type *pos;
	bucket_type *end;
	link_type *link;

	unordered_map_const_iterator(): pos(NULL), end(NULL), link(NULL) {}

	unordered_map_const_iterator(bucket_type *pos_, bucket_type *end_, 
		link_type *link_): pos(pos_), end(end_), link(link_) {}

	unordered_map_const_iterator(const iterator &iter): 
		pos(iter.pos), end(iter.end), link(iter.link) {}

	reference operator *() const
	{
		return *static_cast<node_type *>(link)->valptr();
	}

	pointer operator ->() const
	{
		return static_cast<node_type *>(link)->valptr();
	}

	this_type &operator ++()
	{
		next();
		return *this;
	}

	this_type operator ++(int)
	{
		this_type temp(*this);
		next();
		return temp;
	}

	bool operator ==(const this_type &other) const
	{
		return (this->pos == other.pos) && (this->link == other.link);
	}

	bool operator !=(const this_type &other) const
	{
		return !(*this == other);
	}

	void next()
	{
		// get current bucket next
		link = link->next;

		// reach current bucket end
		if (link == NULL) {
			assert(pos != end);	// if this is end, next is undefined
			// search next non-empty bucket
			for (pos += 1; pos != end && slist_is_empty(pos); ++pos)
				;
			if (pos == end) {	// get bucket end
				link = NULL;
			} else {	// get an non-empty bucket
				link = pos->head.next;
			}
		}
	}
};

/**
 * Unordered map iterator equality comparison.
 */
template <typename T>
inline 
bool operator ==(const unordered_map_iterator<T> &x,
	const unordered_map_const_iterator<T> &y)
{
	return (x.pos == y.pos) && (x.link == y.link);
}

/**
 * Unordered map iterator inequality comparison.
 */
template <typename T>
inline 
bool operator !=(const unordered_map_iterator<T> &x,
	const unordered_map_const_iterator<T> &y)
{
	return !(x == y);
}

/**
 * Unordered Map
 * Unordered maps are associative containers that store elements formed by 
 * the combination of a key value and a mapped value, and which allows 
 * for fast retrieval of individual elements based on their keys.
 */
template <typename Key, typename T, 
	typename Hash = hash<Key>, 
	typename Pred = std::equal_to<Key>, 
	typename Alloc = std::allocator<std::pair<const Key, T> > > 
class unordered_map {
	typedef detail::slist_t bucket_type;
	typedef detail::slist_node_t link_type;
	typedef unordered_map_node<std::pair<const Key, T> > node_type;
	typedef typename Alloc::template rebind<bucket_type>::other bucket_alloc_type;
	typedef typename Alloc::template rebind<node_type>::other node_alloc_type;

	Hash hash_;					// hash function
	Pred equal_;				// equal fucntion
	node_alloc_type node_alloc_;// allocator for node
	bucket_type *buckets_;		// hash table
	size_t bucket_count_;		// bucket count
	float max_load_factor_;		// max load factor

	static const size_t MIN_BUCKET_NUM = 8;
	static const size_t MAX_BUCKET_NUM = ((size_t)1 << (8*sizeof(size_t)-1));
	static const size_t DEFAULT_BUCKET_NUM = 16;
	
public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef std::pair<const key_type, mapped_type> value_type;
	typedef Hash hasher;
	typedef Pred key_equal;
	typedef Alloc allocator_type;

	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef unordered_map_iterator<value_type> iterator;
	typedef unordered_map_const_iterator<value_type> const_iterator;
	typedef unordered_map_local_iterator<value_type> local_iterator;
	typedef unordered_map_const_local_iterator<value_type> const_local_iterator;

	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	/**
	 * empty container constructor (default constructor)
	 * Constructs an empty unordered_map object, containing no elements and 
	 * with a size of zero.
	 * It can construct the container with specific hasher, key_equal and 
	 * allocator objects, along with a minimum number of hash buckets.
	 */
	explicit unordered_map(size_type n = DEFAULT_BUCKET_NUM,
		const hasher &hf = hasher(),
		const key_equal &eql = key_equal(),
		const allocator_type &alloc = allocator_type()):
		hash_(hf), equal_(eql), node_alloc_(alloc), 
		buckets_(NULL), bucket_count_(adjust_buckets(n)), 
		max_load_factor_(1.0)
	{
		check_buckets(bucket_count_);
		initialize();
	}

	explicit unordered_map(const allocator_type &alloc): 
		hash_(hasher()), equal_(key_equal()), node_alloc_(alloc), 
		buckets_(NULL), bucket_count_(DEFAULT_BUCKET_NUM), 
		max_load_factor_(1.0)
	{
		check_buckets(bucket_count_);
		initialize();
	}

	/**
	 * copy constructor
	 * The object is initialized to have the same contents and properties 
	 * as the ump unordered_map object.
	 */
	unordered_map(const unordered_map &ump):
		hash_(ump.hash_), equal_(ump.equal_), node_alloc_(ump.node_alloc_),
		buckets_(NULL), bucket_count_(ump.bucket_count_), 
		max_load_factor_(ump.max_load_factor_)
	{
		check_buckets(bucket_count_);
		initialize();

		try 
		{
			copy_from(ump);
		}
		catch (...)
		{
			finalize();
			throw;
		}
	}

	unordered_map(const unordered_map &ump, const allocator_type &alloc):
		hash_(ump.hash_), equal_(ump.equal_), node_alloc_(alloc),
		buckets_(NULL), bucket_count_(ump.bucket_count_), 
		max_load_factor_(ump.max_load_factor_)
	{
		check_buckets(bucket_count_);
		initialize();

		try 
		{
			copy_from(ump);
		}
		catch (...)
		{
			finalize();
			throw;
		}
	}

#if __cplusplus >= 201103L
	/**
	 * move constructor
	 * The object acquires the contents of the rvalue ump.
	 */
	unordered_map(unordered_map &&ump):
		hash_(std::move(ump.hash_)), equal_(std::move(ump.equal_)),
		node_alloc_(std::move(ump.node_alloc_)),
		buckets_(ump.buckets_), bucket_count_(ump.bucket_count_), 
		max_load_factor_(ump.max_load_factor_)
	{
		ump.buckets_ = NULL;
		ump.bucket_count_ = MIN_BUCKET_NUM;
		ump.max_load_factor_ = 1.0;
		ump.initialize();
	}

	unordered_map(unordered_map &&ump, const allocator_type &alloc):
		hash_(ump.hash_), equal_(ump.equal_), node_alloc_(alloc),
		buckets_(NULL), bucket_count_(ump.bucket_count_), 
		max_load_factor_(ump.max_load_factor_)
	{
		check_buckets(bucket_count_);
		initialize();

		try 
		{
			move_from(std::forward<unordered_map>(ump));
		}
		catch (...)
		{
			finalize();
			throw;
		}
		ump.clear();
	}
#endif // __cplusplus >= 201103L

	/**
	 * range constructor
	 * Constructs an unordered_map object containing copies of each of 
	 * the elements in the range [first,last).
	 */
	template <typename InputIterator>
	unordered_map(InputIterator first, InputIterator last,
		size_type n = DEFAULT_BUCKET_NUM,
		const hasher &hf = hasher(),
		const key_equal &eql = key_equal(),
		const allocator_type &alloc = allocator_type()):
		hash_(hf), equal_(eql), node_alloc_(alloc), 
		buckets_(NULL), bucket_count_(adjust_buckets(n)), 
		max_load_factor_(1.0)
	{
		check_buckets(bucket_count_);
		initialize();
		
		try
		{
			insert(first, last);
		}
		catch (...)
		{
			finalize();
			throw;
		}
	}

#if __cplusplus >= 201103L
	unordered_map(std::initializer_list<value_type> il,
		size_type n = DEFAULT_BUCKET_NUM,
		const hasher &hf = hasher(),
		const key_equal &eql = key_equal(),
		const allocator_type &alloc = allocator_type()):
		unordered_map(il.begin(), il.end(), n, hf, eql, alloc)
	{}
#endif // __cplusplus >= 201103L

	/**
	 * Destroy unordered map
	 * Destructs the container object. This calls each of the contained 
	 * element's destructors, and dealocates all the storage capacity 
	 * allocated by the unordered_map container.
	 */
	~unordered_map() 
	{
		finalize(); 
	}

	/**
	 * Assign content
	 * Assigns ump (or il) as the new content for the container.
	 */
	unordered_map &operator =(const unordered_map &ump)
	{
		if (this == &ump)
			return *this;

		unordered_map temp(ump);
		this->swap_data(temp);
		return *this;
	}

#if __cplusplus >= 201103L
	unordered_map &operator =(unordered_map &&ump)
	{
		using std::swap;

		if (this == &ump)
			return *this;

		clear();
		swap_data(ump);
		swap(node_alloc_, ump.node_alloc_);
		return *this;
	}

	unordered_map &operator =(std::initializer_list<value_type> il)
	{
		clear();
		insert(il.begin(), il.end());
		return *this;
	}
#endif
	
	/**
	 * Test whether container is empty
	 * Returns a bool value indicating whether the unordered_map 
	 * container is empty, i.e. whether its size is 0.
	 */
	bool empty() const noexcept
	{
		for (size_type i = 0; i < bucket_count_; ++i) {
			if (!slist_is_empty(buckets_+i))
				return false;
		}
		return true;
	}

	/**
	 * Return container size
	 * Returns the number of elements in the unordered_map container.
	 */
	size_type size() const noexcept
	{
		size_type sum = 0;
		for (size_type i = 0; i < bucket_count_; ++i) {
			sum += bucket_size(i);
		}
		return sum;
	}

	/**
	 * Return maximum size
	 * Returns the maximum number of elements that the unordered_map 
	 * container can hold.
	 */
	size_type max_size() const noexcept
	{
		return std::numeric_limits<size_type>::max();
	}

	/**
	 * Return iterator to beginning
	 * Returns an iterator pointing to the first element in 
	 * the unordered_map container or in one of its buckets.
	 */
	iterator begin() noexcept
	{
		bucket_type *pos = buckets_;
		bucket_type *last = buckets_+bucket_count_;
		for ( ; pos != last && slist_is_empty(pos); ++pos)
			;
		if (pos == last)
			return end();
		else
			return iterator(pos, last, pos->head.next);
	}

	const_iterator begin() const noexcept 
	{
		const bucket_type *pos = buckets_;
		const bucket_type *last = buckets_+bucket_count_;
		for ( ; pos != last && slist_is_empty(pos); ++pos)
			;
		if (pos == last)
			return end();
		else
			return const_iterator(pos, last, pos->head.next);
	}

	local_iterator begin(size_type n)
	{
		assert(n < bucket_count());
		return local_iterator(buckets_[n].head.next);
	}

	const_local_iterator begin(size_type n) const
	{
		assert(n < bucket_count());
		return const_local_iterator(buckets_[n].head.next);
	}

	/**
	 * Return iterator to end
	 * Returns an iterator pointing to the past-the-end element in 
	 * the unordered_map container or in one of its buckets.
	 */
	iterator end() noexcept
	{
		return iterator(buckets_+bucket_count_, buckets_+bucket_count_, NULL);
	}

	const_iterator end() const noexcept
	{
		return const_iterator(buckets_+bucket_count_, buckets_+bucket_count_, NULL);
	}

	local_iterator end(size_type n)
	{
		assert(n < bucket_count());
		return local_iterator(NULL);
	}

	const_local_iterator end(size_type n) const
	{
		assert(n < bucket_count());
		return const_local_iterator(NULL);
	}

	/**
	 * Return const_iterator to beginning
	 * Returns a const_iterator pointing to the first element in 
	 * the unordered_map container or in one of its buckets.
	 */
	const_iterator cbegin() const noexcept 
	{
		const bucket_type *pos = buckets_;
		const bucket_type *last = buckets_+bucket_count_;
		for ( ; pos != last && slist_is_empty(pos); ++pos)
			;
		if (pos == last)
			return end();
		else
			return const_iterator(pos, last, pos->head.next);
	}

	const_local_iterator cbegin(size_type n) const
	{
		assert(n < bucket_count());
		return const_local_iterator(buckets_[n].head.next);
	}

	/**
	 * Return const_iterator to end
	 * Returns a const_iterator pointing to the past-the-end element in 
	 * the unordered_map container or in one of its buckets.
	 */
	const_iterator cend() const noexcept
	{
		return const_iterator(buckets_+bucket_count_, buckets_+bucket_count_, NULL);
	}

	const_local_iterator cend(size_type n) const
	{
		assert(n < bucket_count());
		return const_local_iterator(NULL);
	}

	/**
	 * Access element
	 * If k matches the key of an element in the container, 
	 * the function returns a reference to its mapped value.
	 */
	mapped_type &operator [](const key_type &k)
	{
		bucket_type *bucket = buckets_+bucket_index(hash_(k));
		link_type *link = 
			slist_search(slist_head(bucket), NULL, k, equal_, get_key);
		if (link == NULL) {	// insert an new pair
			slist_insert_after(slist_before_head(bucket), 
				create_node(k, mapped_type()));
			link = bucket->head.next;
		}
		return get_mapped(link);
	}

	/**
	 * Access element
	 * Returns a reference to the mapped value of the element with key k 
	 * in the unordered_map.
	 */
	mapped_type &at(const key_type &k)
	{
		bucket_type *bucket = buckets_+bucket_index(hash_(k));
		link_type *link = 
            slist_search(slist_head(bucket), NULL, k, equal_, get_key);
		if (link == NULL) {
			throw std::out_of_range("unordered_map::at");
		}
		return get_mapped(link);
	}

	const mapped_type &at(const key_type &k) const
	{
		const bucket_type *bucket = buckets_+bucket_index(hash_(k));
		const link_type *link = 
            slist_search(slist_head(bucket), NULL, k, equal_, get_key);
		if (link == NULL) {
			throw std::out_of_range("unordered_map::at");
		}
		return get_mapped(link);
	}

	/**
	 * Get iterator to element
	 * Searches the container for an element with k as key and returns 
	 * an iterator to it if found, otherwise it returns an iterator to 
	 * unordered_map::end (the element past the end of the container).
	 */
	iterator find(const key_type &k)
	{
		bucket_type *bucket = buckets_+bucket_index(hash_(k));
		link_type *link = 
            slist_search(slist_head(bucket), NULL, k, equal_, get_key);
		if (link == NULL) {
			return end();
		} else {
			return iterator(bucket, buckets_+bucket_count_, link);
		}
	}

	const_iterator find(const key_type &k) const
	{
		const bucket_type *bucket = buckets_+bucket_index(hash_(k));
		const link_type *link = 
            slist_search(slist_head(bucket), NULL, k, equal_, get_key);
		if (link == NULL) {
			return end();
		} else {
			return const_iterator(bucket, buckets_+bucket_count_, link);
		}
	}

	/**
	 * Count elements with a specific key
	 * Searches the container for elements whose key is k and 
	 * returns the number of elements found. 
	 */
	size_type count(const key_type &k) const
	{
		const bucket_type *bucket = buckets_+bucket_index(hash_(k));
		return slist_search(slist_head(bucket), NULL, k, equal_, get_key) == NULL ? 0 : 1;
	}

	/**
	 * Get range of elements with specific key
	 * Returns the bounds of a range that includes all the elements 
	 * in the container with a key that compares equal to k.
	 */
	std::pair<iterator, iterator> equal_range(const key_type &k)
	{
		bucket_type *bucket = buckets_+bucket_index(hash_(k));
		link_type *link = 
            slist_search(slist_head(bucket), NULL, k, equal_, get_key);
		if (link == NULL) {
			return std::make_pair(end(), end());
		} else {
			iterator lower(bucket, buckets_+bucket_count_, link);
			iterator upper(lower);
			upper.next();
			return std::make_pair(lower, upper);
		}
	}

	std::pair<const_iterator, const_iterator> 
	equal_range(const key_type &k) const
	{
		const bucket_type *bucket = buckets_+bucket_index(hash_(k));
		const link_type *link = 
            slist_search(slist_head(bucket), NULL, k, equal_, get_key);
		if (link == NULL) {
			return std::make_pair(end(), end());
		} else {
			const_iterator lower(bucket, buckets_+bucket_count_, link);
			const_iterator upper(lower);
			upper.next();
			return std::make_pair(lower, upper);
		}
	}

#if __cplusplus >= 201103L
	/**
	 * Construct and insert element
	 * Inserts a new element in the unordered_map if its key is unique. 
	 * This new element is constructed in place using args as the arguments 
	 * for the element's constructor.
	 */
	template <typename ... Args>
	std::pair<iterator, bool> emplace(Args &&... args)
	{
		return insert(value_type(std::forward<Args>(args) ...));
	}

	/**
	 * Construct and insert element with hint
	 * Inserts a new element in the unordered_map if its key is unique. 
	 * This new element is constructed in place using args as the arguments 
	 * for the element's constructor. position points to a location in the 
	 * container suggested as a hint on where to start the search 
	 * for its insertion point. 
	 */
	template <typename ... Args>
	std::pair<iterator, bool> emplace_hint(const_iterator position, 
		Args &&... args)
	{
		return insert(position, value_type(std::forward<Args>(args) ...));
	}
#endif // __cplusplus >= 201103L

	/**
	 * Insert elements
	 * Inserts new elements in the unordered_map.
	 */
	std::pair<iterator, bool> insert(const value_type &val)
	{
		bucket_type *bucket = buckets_+bucket_index(hash_(val.first));
		link_type *link = 
            slist_search(slist_head(bucket), NULL, val.first, equal_, get_key);
		if (link == NULL) {	// insert an new pair
			slist_insert_after(slist_before_head(bucket), create_node(val));
			return std::make_pair(
				iterator(bucket, buckets_+bucket_count_, bucket->head.next), true);
		} else {	// key is already in table
			return std::make_pair(
				iterator(bucket, buckets_+bucket_count_, link), false);
		}
	}

	iterator insert(const_iterator hint, const value_type &val)
	{
		return insert(val).first;
	}

	template <typename InputIterator>
	void insert(InputIterator first, InputIterator last)
	{
		for ( ; first != last; ++first) {
			const value_type &val = *first;
			bucket_type *bucket = buckets_+bucket_index(hash_(val.first));
			link_type *link = 
                slist_search(slist_head(bucket), NULL, val.first, equal_, get_key);
			if (link == NULL) {	// insert an new pair
				slist_insert_after(slist_before_head(bucket), create_node(val));
			}
		}
	}

#if __cplusplus >= 201103L
	template <typename P>
	std::pair<iterator, bool> insert(P &&val)
	{
		bucket_type *bucket = buckets_+bucket_index(hash_(val.first));
		link_type *link = 
            slist_search(slist_head(bucket), NULL, val.first, equal_, get_key);
		if (link == NULL) {	// insert an new pair
			slist_insert_after(slist_before_head(bucket), 
				create_node(std::forward<P>(val)));
			return std::make_pair(
				iterator(bucket, buckets_+bucket_count_, bucket->head.next), true);
		} else {	// key is already in table
			return std::make_pair(
				iterator(bucket, buckets_+bucket_count_, link), false);
		}
	}

	template <typename P>
	iterator insert(const_iterator hint, P &&val)
	{
		return insert(std::forward<P>(val)).first;
	}

	void insert(std::initializer_list<value_type> il)
	{
		insert(il.begin(), il.end());
	}
#endif // __cplusplus >= 201103L

	/**
	 * Erase elements
	 * Removes from the unordered_map container a single element 
	 */
	iterator erase(const_iterator position)
	{
		assert(position.pos != NULL && position.link != NULL);
		link_type *prev = slist_get_prev(&position.pos->head, position.link);
		destroy_node(slist_remove_after(prev));
		iterator iter((bucket_type *) position.pos, 
			(bucket_type *) position.end, prev);
		return ++iter;
	}

	size_type erase(const key_type &k)
	{
		bucket_type *bucket = buckets_+bucket_index(hash_(k));
		link_type *prev;
		link_type *link = slist_search_after(slist_before_head(bucket), NULL, 
            k, equal_, get_key, &prev);
		if (link == NULL) {
			return 0;
		} else {
			destroy_node(slist_remove_after(prev));
			return 1;
		}
	}

	iterator erase(const_iterator first, const_iterator last)
	{
		while (first != last) {
			first = erase(first);
		}
		return iterator((bucket_type *) last.pos, 
			(bucket_type *) last.end, (link_type *) last.link);
	}

	/**
	 * Clear content
	 * All the elements in the unordered_map container are dropped: 
	 * their destructors are called, and they are removed from the container, 
	 * leaving it with a size of 0.
	 */
	void clear() noexcept
	{
		bucket_type *bucket = buckets_;
		bucket_type *last = buckets_+bucket_count_;
		for ( ; bucket != last; ++bucket) {
			slist_destroy(bucket, destroy(node_alloc_)); 
			slist_init(bucket);
		}
	}

	/**
	 * Swap content
	 * Exchanges the content of the container by the content of ump, 
	 * which is another unordered_map object containing elements 
	 * of the same type. Sizes may differ.
	 */
	void swap(unordered_map &ump)
	{
		using std::swap;

		swap_data(ump);
		swap(node_alloc_, ump.node_alloc_);
	}

	/**
	 * Return number of buckets
	 * Returns the number of buckets in the unordered_map container.
	 */
	size_type bucket_count() const noexcept
	{
		return bucket_count_;
	}

	/**
	 * Return maximum number of buckets
	 * Returns the maximum number of buckets that the unordered_map 
	 * container can have.
	 */
	size_type max_bucket_count() const noexcept
	{
		return MAX_BUCKET_NUM;
	}

	/**
	 * Return bucket size
	 * Returns the number of elements in bucket n.
	 */
	size_type bucket_size(size_type n) const
	{
		assert(n < bucket_count());
		return slist_size(buckets_+n);
	}

	/**
	 * Locate element's bucket
	 * Returns the bucket number where the element with key k is located.
	 */
	size_type bucket(const key_type &k) const
	{
		return bucket_size(bucket_index(hash_(k)));
	}

	/**
	 * Return load factor
	 * Returns the current load factor in the unordered_map container.
	 */
	float load_factor() const noexcept
	{
		return (float) size() / bucket_count();
	}

	/**
	 * Get maximum load factor
	 * returns the current maximum load factor for the unordered_map container.
	 */
	float max_load_factor() const noexcept
	{
		return max_load_factor_;
	}

	/**
	 * Set maximum load factor
	 * sets z as the new maximum load factor for the unordered_map container.
	 */
	void max_load_factor(float z)
	{
		max_load_factor_ = z;
	}

	/**
	 * Set number of buckets
	 * Sets the number of buckets in the container to n or more.
	 */
	void rehash(size_type n)
	{
		size_type buckets_num =
			adjust_buckets(std::max<size_type>(n, size()/max_load_factor()));
		do_rehash(buckets_num);
	}

	/**
	 * Request a capacity change
	 * Sets the number of buckets in the container (bucket_count)
	 * to the most appropriate to contain at least n elements.
	 */
	void reserve(size_type n)
	{
		size_type buckets_num = 
			adjust_buckets(std::max(n, size())/max_load_factor());
		do_rehash(buckets_num);
	}

	/**
	 * Shrink to specified bucket count
	 * Requests the container to reduce its buckets to specified bucket count.
	 */
	void shrink(size_type n)
	{
		do_shrink(adjust_buckets(n));
	}

	/**
	 * Shrink to fit
	 * Requests the container to reduce its buckets to fit its size.
	 */
	void shrink_to_fit()
	{
		shrink(adjust_buckets(size()/max_load_factor()));
	}

	/**
	 * Get hash function
	 * Returns the hash function object used by the hash_map container.
	 */
	hasher hash_function() const
	{
		return hash_;
	}

	/**
	 * Get key equivalence predicate
	 * Returns the key equivalence comparison predicate used
	 * by the hash_map container.
	 */
	key_equal key_eq() const
	{
		return equal_;
	}

	/**
	 * Get allocator
	 * Returns the allocator object used to construct the container.
	 */
	allocator_type get_allocator() const
	{
		return allocator_type(node_alloc_);
	}

	/**
	 * Relational operators for unordered_map
	 * These overloaded global operator functions perform the appropriate 
	 * equality or inequality comparison operation between the unordered_map 
	 * containers lhs and rhs.
	 */
	bool operator ==(const unordered_map &other) const
	{
		return (size() == other.size() && 
			contain(other) && other.contain(*this));
	}

	bool operator !=(const unordered_map &other) const
	{
		return !(this->operator ==(other));
	}

private:
	static size_type adjust_buckets(size_type buckets_num)
	{
		if (buckets_num > MAX_BUCKET_NUM) {
			return MAX_BUCKET_NUM;
		}

		size_type n = MIN_BUCKET_NUM;
		while (n < buckets_num) {
			n = n << 1;
		}
		return n;
	}

	static void check_buckets(size_type buckets_num)
	{
		assert(buckets_num >= MIN_BUCKET_NUM); 
		assert(buckets_num <= MAX_BUCKET_NUM); 
		assert((buckets_num & (buckets_num-1)) == 0);
	}

	static size_type bucket_index(size_type hash_val, size_type buckets_num)
	{
		return hash_val & (buckets_num-1);
	}

	size_type bucket_index(size_type hash_val) const
	{
		return bucket_index(hash_val, bucket_count_);
	}

	void copy_from(const unordered_map &ump)
	{
		bucket_type *first = ump.buckets_; 
		bucket_type *last = ump.buckets_+ump.bucket_count_;

		for (bucket_type *pos = first; pos != last; ++pos) {
			if (slist_is_empty(pos))
				continue;
			bucket_type *bucket = buckets_+(pos-first);
			link_type *link = pos->head.next;
			for ( ; link != NULL; link = link->next) {
				node_type *node = static_cast<node_type *>(link);
				slist_insert_after(slist_before_head(bucket), 
					create_node(*node->valptr()));
			}
		}
	}

#if __cplusplus >= 201103L
	void move_from(unordered_map &&ump)
	{
		bucket_type *first = ump.buckets_; 
		bucket_type *last = ump.buckets_+ump.bucket_count_;

		for (bucket_type *pos = first; pos != last; ++pos) {
			if (slist_is_empty(pos))
				continue;
			bucket_type *bucket = buckets_+(pos-first);
			link_type *link = pos->head.next;
			for ( ; link != NULL; link = link->next) {
				node_type *node = static_cast<node_type *>(link);
				slist_insert_after(slist_before_head(bucket), 
					create_node(std::move(*node->valptr())));
			}
		}
	}
#endif // __cplusplus >= 201103L

	void do_rehash(size_type n)
	{
		check_buckets(n);

		if (n <= bucket_count())
			return;

		// allocate new table 
		bucket_type *new_buckets = bucket_alloc_type(node_alloc_).allocate(n);
		for (size_type i = 0; i < n; ++i)
			slist_init(new_buckets+i);

		// rehash and transfer node to new table
		bucket_type *bucket = buckets_;
		bucket_type *last = buckets_+bucket_count_;
		for ( ; bucket != last; ++bucket) {
			if (slist_is_empty(bucket))
				continue;
			link_type *link = bucket->head.next;
			link_type *keep;
			while (link != NULL) {
				keep = link->next;
				bucket_type *bucket = 
					new_buckets+bucket_index(hash_(get_key(link)), n);
				slist_insert_after(slist_before_head(bucket), link);
				link = keep;
			}
		}
		
		// deallocate old table
		bucket_alloc_type(node_alloc_).deallocate(buckets_, bucket_count_);
		buckets_ = new_buckets;
		bucket_count_ = n;
	}

	void do_shrink(size_type n)
	{
		check_buckets(n);

		if (n >= bucket_count())
			return;

		// allocate new table 
		bucket_type *new_buckets = bucket_alloc_type(node_alloc_).allocate(n);
		for (size_type i = 0; i < n; ++i)
			slist_init(new_buckets+i);

		// shrink and transfer node to new table
		bucket_type *bucket = buckets_;
		bucket_type *last = buckets_+bucket_count_;
		size_type i = 0;
		for ( ; bucket != last; ++bucket, ++i) {
			if (i == n) i = 0;
			if (slist_is_empty(bucket)) 
				continue;
			slist_transfer_after(&new_buckets[i].head, &bucket->head, NULL);
		}
		
		// deallocate old table
		bucket_alloc_type(node_alloc_).deallocate(buckets_, bucket_count_);
		buckets_ = new_buckets;
		bucket_count_ = n;
	}

	void swap_data(unordered_map &ump)
	{
		std::swap(buckets_, ump.buckets_);
		std::swap(bucket_count_, ump.bucket_count_);
		std::swap(max_load_factor_, ump.max_load_factor_);
	}

	bool contain(const unordered_map &ump) const
	{
		const_iterator pos = ump.begin();
		const_iterator last = ump.end(); 
		const_iterator this_last = this->end();
		for ( ; pos != last; ++pos) {
			const_iterator this_pos = this->find(pos->first);
			if (this_pos == this_last || this_pos->second != pos->second)
				return false;
		}
		return true;
	}

	node_type *get_node()
	{
		return node_alloc_.allocate(1);
	}

	void put_node(node_type *node)
	{
		node_alloc_.deallocate(node, 1);
	}

#if __cplusplus >= 201103L
	template <typename ...Args>
	link_type *create_node(Args &&...args)
	{
		node_type *node = get_node();
		try
		{
			allocator_type(node_alloc_).construct(
				node->valptr(), std::forward<Args>(args)...);
		}
		catch (...)
		{
			put_node(node);
			throw;
		}
		return static_cast<link_type *>(node);
	}
#else // !( __cplusplus >= 201103L )
	link_type *create_node(const value_type &val)
	{
		node_type *node = get_node();
		try
		{
			allocator_type(node_alloc_).construct(node->valptr(), val);
		}
		catch (...)
		{
			put_node(node);
			throw;
		}
		return static_cast<link_type *>(node);
	}

	link_type *create_node(const key_type &k, const mapped_type &mval)
	{
		node_type *node = get_node();
		try
		{
			::new (node->valptr()) value_type(k, mval);
		}
		catch (...)
		{
			put_node(node);
			throw;
		}
		return static_cast<link_type *>(node);
	}
#endif // __cplusplus >= 201103L

	struct destroy {
		node_alloc_type *node_alloc;

		destroy(node_alloc_type &node_alloc_): node_alloc(&node_alloc_) {}
	
		void operator ()(link_type *link)
		{
			node_type *node = static_cast<node_type *>(link);
			allocator_type(*node_alloc).destroy(node->valptr());
			node_alloc->deallocate(node, 1);
		}
	};

	void destroy_node(link_type *link)
	{
		destroy(node_alloc_).operator ()(link);
	}

	static const key_type &get_key(const link_type *link)
	{
		const node_type *node = static_cast<const node_type *>(link);
		return node->valptr()->first;
	}

	static mapped_type &get_mapped(link_type *link)
	{
		node_type *node = static_cast<node_type *>(link);
		return node->valptr()->second;
	}

	static const mapped_type &get_mapped(const link_type *link)
	{
		const node_type *node = static_cast<const node_type *>(link);
		return node->valptr()->second;
	}

	void initialize()
	{
		buckets_ = bucket_alloc_type(node_alloc_).allocate(bucket_count_);
		for (size_type i = 0; i < bucket_count_; ++i)
			slist_init(buckets_+i);
	}

	void finalize()
	{
		for (size_type i = 0; i < bucket_count_; ++i)
			slist_destroy(buckets_+i, destroy(node_alloc_)); 
		bucket_alloc_type(node_alloc_).deallocate(buckets_, bucket_count_);
	}
};

} // namespace Hx

#endif // HX_UNORDERED_MAP_H

