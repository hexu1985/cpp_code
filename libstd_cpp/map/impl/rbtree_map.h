// -*- C++ -*-
// HeXu's
// 2014 Jan

#ifndef HX_RBTREE_MAP_H
#define HX_RBTREE_MAP_H

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
#include "rbtree_impl.h"

namespace Hx {

/**
 * A helper node class for map.
 * This is just a linked list with uninitialized storage for a
 * data value in each node.
 */
template <typename T>
struct map_node: public detail::rbtree_node_t {
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

template <typename T>
struct map_iterator {
	typedef detail::bintree_t tree_type;
	typedef detail::bintree_node_t link_type;

	tree_type *tree;
	link_type *link;

	typedef map_iterator<T> this_type;
	typedef map_node<T> node_type;

	typedef T value_type;
	typedef T *pointer;
	typedef T &reference;
	typedef ptrdiff_t difference_type;
	typedef std::bidirectional_iterator_tag iterator_category;

	map_iterator(): tree(NULL), link(NULL) {}

	explicit map_iterator(tree_type *tree_, link_type *link_): 
		tree(tree_), link(link_) {}

	reference operator *() const 
	{
		return *static_cast<node_type *>(link)->valptr();
	}

	pointer operator ->() const 
	{
		return static_cast<node_type *>(link)->valptr();
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

	bool operator ==(const this_type &other) const
	{
		return (this->tree == other.tree && this->link == other.link);
	}

	bool operator !=(const this_type &other) const
	{
		return !(*this == other);
	}

	void next() 
	{
		if (link == NULL)
			link = bintree_minimum(tree->root);
		else
			link = bintree_successor(link); 
	}

	void prev() 
	{
		if (link == NULL)
			link = bintree_maximum(tree->root);
		else
			link = bintree_predecessor(link); 
	}
};

template <typename T>
struct map_const_iterator {
	typedef const detail::bintree_t tree_type;
	typedef const detail::bintree_node_t link_type;

	tree_type *tree;
	link_type *link;

	typedef map_const_iterator<T> this_type;
	typedef const map_node<T> node_type;
	typedef map_iterator<T> iterator;

	typedef T value_type;
	typedef const T *pointer;
	typedef const T &reference;
	typedef ptrdiff_t difference_type;
	typedef std::bidirectional_iterator_tag iterator_category;

	map_const_iterator(): tree(NULL), link(NULL) {}

	explicit map_const_iterator(tree_type *tree_, link_type *link_): 
		tree(tree_), link(link_) {}

	map_const_iterator(const iterator &iter): tree(iter.tree), link(iter.link) 
	{}

	reference operator *() const 
	{
		return *static_cast<node_type *>(link)->valptr();
	}

	pointer operator ->() const 
	{ 
		return static_cast<node_type *>(link)->valptr();
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

	bool operator ==(const this_type &other) const
	{
		return (this->tree == other.tree && this->link == other.link);
	}

	bool operator !=(const this_type &other) const
	{
		return !(*this == other);
	}

	void next()
	{
		if (link == NULL)
			link = bintree_minimum(tree->root);
		else
			link = bintree_successor(link); 
	}

	void prev()
	{
		if (link == NULL)
			link = bintree_maximum(tree->root);
		else
			link = bintree_predecessor(link); 
	}
};

/**
 * Map iterator equality comparison.
 */
template <typename T>
inline 
bool operator ==(const map_iterator<T> &x, const map_const_iterator<T> &y)
{
	return (x.tree == y.tree && x.link == y.link);
}

/**
 * Map iterator inequality comparison.
 */
template <typename T>
inline 
bool operator !=(const map_iterator<T> &x, const map_const_iterator<T> &y)
{
	return !(x == y);
}

template <typename Key, typename T,
	typename Compare = std::less<Key>,
	typename Alloc = std::allocator<std::pair<const Key, T> > >
class map {
	typedef detail::bintree_t tree_type;
	typedef detail::bintree_node_t link_type;
	typedef map_node<std::pair<const Key, T> > node_type;
	typedef typename Alloc::template rebind<node_type>::other node_alloc_type;

	Compare less_;
	node_alloc_type node_alloc_;
	tree_type tree_;

public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef std::pair<const key_type, mapped_type> value_type;
	typedef Compare key_compare;

#if __cplusplus >= 201103L
	struct value_compare {
		Compare comp;
		value_compare(Compare c): comp(c) {}

		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;

		bool operator ()(const value_type &x, const value_type &y) const
		{
			return comp(x.first, y.first);
		}
	};
#else // !( __cplusplus >= 201103L )
	struct value_compare: 
		public std::binary_function<value_type, value_type, bool> {
		Compare comp;
		value_compare(Compare c): comp(c) {}

		bool operator ()(const value_type &x, const value_type &y) const
		{
			return comp(x.first, y.first);
		}
	};
#endif // __cplusplus >= 201103L

	typedef Alloc allocator_type;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef map_iterator<value_type> iterator;
	typedef map_const_iterator<value_type> const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

	/**
	 * empty container constructor (default constructor)
	 * Constructs an empty container, with no elements.
	 */
	explicit map(const key_compare &comp = key_compare(),
		const allocator_type &alloc = allocator_type()): 
		less_(comp), node_alloc_(alloc)
	{
		initialize();
	}

#if __cplusplus >= 201103L
	explicit map(const allocator_type &alloc): map(key_compare(), alloc) {}
#else // !( __cplusplus >= 201103L )
	explicit map(const allocator_type &alloc): 
		less_(key_compare()), node_alloc_(alloc)
	{
		initialize();
	}
#endif // __cplusplus >= 201103L

	/**
	 * range constructor
	 * Constructs a container with as many elements as the 
	 * range [first,last), with each element constructed 
	 * from its corresponding element in that range.
	 */
	template <typename InputIterator>
	map(InputIterator first, InputIterator last, 
		const key_compare &comp = key_compare(),
		const allocator_type &alloc = allocator_type()): 
		less_(comp), node_alloc_(alloc)
	{
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

	map(const map &x): less_(x.less_), node_alloc_(x.node_alloc_)
	{
		try
		{
			bintree_copy(&tree_, &x.tree_, clone(node_alloc_));
		}
		catch (...)
		{
			finalize();
			throw;
		}
	}

	map(const map &x, const allocator_type &alloc): 
		less_(x.less_), node_alloc_(alloc)
	{
		try
		{
			bintree_copy(&tree_, &x.tree_, clone(node_alloc_));
		}
		catch (...)
		{
			finalize();
			throw;
		}
	}

#if __cplusplus >= 201103L
	map(map &&x): 
		less_(x.less_), node_alloc_(std::move(x.node_alloc_)), tree_(x.tree_)
	{
		x.initialize();
	}

	map(map &&x, const allocator_type &alloc): 
		less_(x.less_), node_alloc_(alloc)
	{
		try
		{
			bintree_copy(&tree_, &x.tree_, move_clone(node_alloc_));
		}
		catch (...)
		{
			finalize();
			throw;
		}
	}
#endif // __cplusplus >= 201103L

#if __cplusplus >= 201103L
	map(std::initializer_list<value_type> il,
		const key_compare &comp = key_compare(),
		const allocator_type &alloc = allocator_type()): 
		map(il.begin(), il.end(), comp, alloc)
	{}
#endif // __cplusplus >= 201103L

	/**
	 * Map destructor
	 * Destroys the container object.
	 */
	~map()
	{
		finalize();
	}

	/**
	 * Copy container content
	 * Assigns new contents to the container, replacing its current content.
	 */
	map &operator =(const map &x)
	{
		if (this == &x)
			return *this;

		map tmp(x);
		this->swap_data(tmp);
		return *this;
	}

#if __cplusplus >= 201103L
	map &operator =(map &&x)
	{
		using std::swap;

		if (this == &x)
			return *this;

		clear();
		swap_data(x);
		swap(node_alloc_, x.node_alloc_);
		return *this;
	}

	map &operator =(std::initializer_list<value_type> il)
	{
		clear();
		insert(il.begin(), il.end());
		return *this;
	}
#endif
	
	/**
	 * Return iterator to beginning
	 * Returns an iterator referring to the first element in the map container.
	 */
	iterator begin() noexcept
	{
		if (empty())
			return end();
		return iterator(&tree_, bintree_minimum(tree_.root));
	}

	const_iterator begin() const noexcept
	{
		if (empty())
			return end();
		return const_iterator(&tree_, bintree_minimum(tree_.root));
	}

	/**
	 * Return iterator to end
	 * Returns an iterator referring to the past-the-end element 
	 * in the map container.
	 */
	iterator end() noexcept
	{
		return iterator(&tree_, NULL);
	}

	const_iterator end() const noexcept
	{
		return const_iterator(&tree_, NULL);
	}

	/**
	 * Return reverse iterator to reverse beginning
	 * Returns a reverse iterator pointing to the last element in the container 
	 * (i.e., its reverse beginning).
	 */
	reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

	const_reverse_iterator rbegin() const noexcept 
	{
		return const_reverse_iterator(end()); 
	}

	/**
	 * Return reverse iterator to reverse end
	 * Returns a reverse iterator pointing to the theoretical element 
	 * right before the first element in the map container 
	 * (which is considered its reverse end).
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
	const_iterator cbegin() const noexcept
	{
		if (empty())
			return end();
		return const_iterator(&tree_, bintree_minimum(tree_.root));
	}

	/**
	 * Return const_iterator to end
	 * Returns a const_iterator pointing to the past-the-end element 
	 * in the container.
	 */
	const_iterator cend() const noexcept
	{
		return const_iterator(&tree_, NULL);
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
	 * Test whether container is empty
	 * Returns whether the map container is empty 
	 * (i.e. whether its size is 0).
	 */
	bool empty() const noexcept
	{
		return bintree_is_empty(&tree_);
	}

	/**
	 * Return container size
	 * Returns the number of elements in the map container.
	 */
	size_type size() const noexcept
	{
		return bintree_size(&tree_);
	}

	/**
	 * Access element
	 * If k matches the key of an element in the container, 
	 * the function returns a reference to its mapped value.
	 */
	mapped_type &operator [](const key_type &k)
	{
		link_type *hint = NULL;
		link_type *link = bintree_search(tree_.root, k, less_, get_key, &hint);
		if (link == NULL) {	// k not in map
			link = create_node(k, mapped_type());
			rbtree_insert(&tree_, link, less_, get_key, hint);
		}
		return static_cast<node_type *>(link)->valptr()->second;
	}

#if __cplusplus >= 201103L
	mapped_type &operator [](key_type &&k)
	{
		link_type *hint = NULL;
		link_type *link = bintree_search(tree_.root, k, less_, get_key, &hint);
		if (link == NULL) {	// k not in map
			link = create_node(std::move(k), mapped_type());
			rbtree_insert(&tree_, link, less_, get_key, hint);
		}
		return static_cast<node_type *>(link)->valptr()->second;
	}
#endif // __cplusplus >= 201103L

	/**
	 * Access element
	 * Returns a reference to the mapped value of the element 
	 * identified with key k.
	 */
	mapped_type &at(const key_type &k)
	{
		link_type *link = bintree_search(tree_.root, k, less_, get_key);
		if (link == NULL) {	// k not in map
			throw std::out_of_range(__func__);
		}
		return static_cast<node_type *>(link)->valptr()->second;
	}

	const mapped_type &at(const key_type &k) const
	{
		const link_type *link = bintree_search(tree_.root, k, less_, get_key);
		if (link == NULL) {	// k not in map
			throw std::out_of_range(__func__);
		}
		return static_cast<const node_type *>(link)->valptr()->second;
	}

	/**
	 * Insert elements
	 * Extends the container by inserting new elements, effectively increasing 
	 * the container size by the number of elements inserted.
	 */
	std::pair<iterator, bool> insert(const value_type &val)
	{
		link_type *hint = NULL;
		link_type *link = 
			bintree_search(tree_.root, val.first, less_, get_key, &hint);
		if (link == NULL) {
			link = create_node(val);
			rbtree_insert(&tree_, link, less_, get_key, hint);
			return std::make_pair(iterator(&tree_, link), true);
		} else {
			return std::make_pair(iterator(&tree_, link), false);
		}
	}

	iterator insert(const_iterator position, const value_type &val)
	{
		return insert(val).first;
	}

	template <typename InputIterator>
	void insert(InputIterator first, InputIterator last)
	{
		for ( ; first != last; ++first) {
			const value_type &val = *first;
			link_type *hint = NULL;
			link_type *link = 
				bintree_search(tree_.root, val.first, less_, get_key, &hint);
			if (link == NULL) {
				link = create_node(val);
				rbtree_insert(&tree_, link, less_, get_key, hint);
			}
		}
	}

#if __cplusplus >= 201103L
	template <typename P>
	std::pair<iterator, bool> insert(P &&val)
	{
		link_type *hint = NULL;
		link_type *link =
			bintree_search(tree_.root, val.first, less_, get_key, &hint);
		if (link == NULL) {
			link = create_node(std::forward<P>(val));
			rbtree_insert(&tree_, link, less_, get_key, hint);
			return std::make_pair(iterator(&tree_, link), true);
		} else {
			return std::make_pair(iterator(&tree_, link), false);
		}
	}

	template <typename P>
	iterator insert(const_iterator position, P &&val)
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
	 * Removes from the map container either a single element or 
	 * a range of elements ([first,last)).
	 */
	iterator erase(const_iterator position)
	{
		iterator next((tree_type *) position.tree, (link_type *) position.link);
		++next;
		rbtree_remove(&tree_, (link_type *) position.link);
		destroy_node((link_type *) position.link);
		return next;
	}

	size_type erase(const key_type &k)
	{
		link_type *link = bintree_search(tree_.root, k, less_, get_key);
		if (link == NULL) {
			return 0;
		} else {
			rbtree_remove(&tree_, link);
			destroy_node(link);
			return 1;
		}
	}

	iterator erase(const_iterator first, const_iterator last)
	{
		while (first != last) {
			first = erase(first);
		}
		return iterator((tree_type *) last.tree, (link_type *) last.link);
	}

	/**
	 * Swap content
	 * Exchanges the content of the container by the content of x, 
	 * which is another map of the same type. Sizes may differ.
	 */
	void swap(map &x)
	{
		using std::swap;

		swap_data(x);
		swap(node_alloc_, x.node_alloc_);
	}

	/**
	 * Clear content
	 * Removes all elements from the map container (which are destroyed), 
	 * leaving the container with a size of 0.
	 */
	void clear() noexcept
	{
		finalize();
		initialize();
	}

#if __cplusplus >= 201103L
	/**
	 * Construct and insert element
	 * Inserts a new element in the map if its key is unique. 
	 * This new element is constructed in place using args as the arguments for 
	 * the construction of a value_type (which is an object of a pair type).
	 */
	template <typename ... Args>
	std::pair<iterator, bool> emplace(Args &&... args)
	{
		link_type *new_link = create_node(std::forward<Args>(args) ...);
		link_type *hint = NULL;
		link_type *link = bintree_search(tree_.root, get_key(new_link), 
			less_, get_key, &hint);
		if (link == NULL) {
			rbtree_insert(&tree_, new_link, less_, get_key, hint);
			return std::make_pair(iterator(&tree_, new_link), true);
		} else {
			destroy_node(new_link);
			return std::make_pair(iterator(&tree_, link), false);
		}
	}

	/**
	 * Construct and insert element with hint
	 * Inserts a new element in the map if its key is unique, 
	 * with a hint on the insertion position. This new element is constructed 
	 * in place using args as the arguments for the construction of 
	 * a value_type (which is an object of a pair type).
	 */
	template <typename ... Args>
	iterator emplace_hint(const_iterator position, Args &&... args)
	{
		return emplace(std::forward<Args>(args) ...).first;
	}
#endif // __cplusplus >= 201103L

	/**
	 * Return key comparison object
	 * Returns a copy of the comparison object used by the container 
	 * to compare keys.
	 */
	key_compare key_comp() const
	{
		return less_;
	}

	/**
	 * Return value comparison object
	 * Returns a comparison object that can be used to compare two elements to 
	 * get whether the key of the first one goes before the second.
	 */
	value_compare value_comp() const
	{
		return value_compare(less_);
	}

	/**
	 * Get iterator to element
	 * Searches the container for an element with a key equivalent to k and 
	 * returns an iterator to it if found, otherwise it 
	 * returns an iterator to map::end.
	 */
	iterator find(const key_type &k)
	{
		link_type *pos = bintree_search(tree_.root, k, less_, get_key);
		if (pos == NULL)
			return end();
		else
			return iterator(&tree_, pos);
	}

	const_iterator find(const key_type &k) const
	{
		const link_type *pos = bintree_search(tree_.root, k, less_, get_key);
		if (pos == NULL)
			return end();
		else
			return const_iterator(&tree_, pos);
	}

	/**
	 * Count elements with a specific key
	 * Searches the container for elements with a key equivalent to 
	 * k and returns the number of matches.
	 */
	size_type count(const key_type &k) const
	{
		return (bintree_search(tree_.root, k, less_, get_key) == NULL ?  0 : 1);
	}

	/**
	 * Return iterator to lower bound
	 * Returns an iterator pointing to the first element in the 
	 * container whose key is not considered to go before k 
	 * (i.e., either it is equivalent or goes after).
	 */
	iterator lower_bound(const key_type &k)
	{
		link_type *hint = NULL;
		link_type *link = bintree_search(tree_.root, k, less_, get_key, &hint);
		if (link == NULL) {
			if (less_(k, get_key(hint))) {
				return iterator(&tree_, hint);
			} else {
				return iterator(&tree_, bintree_successor(hint));
			}
		} else {
			return iterator(&tree_, link);
		}
	}

	const_iterator lower_bound(const key_type &k) const
	{
		link_type *hint = NULL;
		link_type *link = bintree_search(tree_.root, k, less_, get_key, &hint);
		if (link == NULL) {
			if (less_(k, get_key(hint))) {
				return const_iterator(&tree_, hint);
			} else {
				return const_iterator(&tree_, bintree_successor(hint));
			}
		} else {
			return const_iterator(&tree_, link);
		}
	}

	/**
	 * Return iterator to upper bound
	 * Returns an iterator pointing to the first element in the container 
	 * whose key is considered to go after k.
	 */
	iterator upper_bound(const key_type &k)
	{
		link_type *hint = NULL;
		link_type *link = bintree_search(tree_.root, k, less_, get_key, &hint);
		if (link == NULL) {
			if (less_(k, get_key(hint))) {
				return iterator(&tree_, hint);
			} else {
				return iterator(&tree_, bintree_successor(hint));
			}
		} else {
			return iterator(&tree_, bintree_successor(link));
		}
	}

	const_iterator upper_bound(const key_type &k) const
	{
		link_type *hint = NULL;
		link_type *link = bintree_search(tree_.root, k, less_, get_key, &hint);
		if (link == NULL) {
			if (less_(k, get_key(hint))) {
				return const_iterator(&tree_, hint);
			} else {
				return const_iterator(&tree_, bintree_successor(hint));
			}
		} else {
			return const_iterator(&tree_, bintree_successor(link));
		}
	}

	/**
	 * Get range of equal elements
	 * Returns the bounds of a range that includes all the elements in 
	 * the container which have a key equivalent to k.
	 */
	std::pair<iterator, iterator> equal_range(const key_type &k)
	{
		link_type *hint = NULL;
		link_type *link = bintree_search(tree_.root, k, less_, get_key, &hint);
		if (link == NULL) {
			if (less_(k, get_key(hint))) {
				iterator iter(&tree_, hint);
				return make_pair(iter, iter);
			} else {
				iterator iter(&tree_, bintree_successor(hint));
				return make_pair(iter, iter);
			}
		} else {
			return make_pair(iterator(&tree_, link), 
				iterator(&tree_, bintree_successor(link)));
		}
	}

	std::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
	{
		link_type *hint = NULL;
		link_type *link = bintree_search(tree_.root, k, less_, get_key, &hint);
		if (link == NULL) {
			if (less_(k, get_key(hint))) {
				const_iterator iter(&tree_, hint);
				return make_pair(iter, iter);
			} else {
				const_iterator iter(&tree_, bintree_successor(hint));
				return make_pair(iter, iter);
			}
		} else {
			return make_pair(const_iterator(&tree_, link), 
				const_iterator(&tree_, bintree_successor(link)));
		}
	}

	/**
	 * Get allocator
	 * Returns a copy of the allocator object associated with the map.
	 */
	allocator_type get_allocator() const noexcept
	{
		return allocator_type(node_alloc_);
	}

private:
	void swap_data(map &x)
	{
		std::swap(tree_, x.tree_);
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
		return node;
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
		return node;
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
		return node;
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

	struct clone {
		node_alloc_type *node_alloc;

		clone(node_alloc_type &node_alloc_): node_alloc(&node_alloc_) {}
	
		link_type *operator ()(const link_type *link)
		{
			const node_type *node = static_cast<const node_type *>(link);
			node_type *new_node = node_alloc->allocate(1);
			try
			{
				allocator_type(*node_alloc).construct(new_node->valptr(), 
					*node->valptr());
			}
			catch (...)
			{
				node_alloc->deallocate(new_node, 1);
				throw;
			}
			new_node->left = NULL;
			new_node->right = NULL;
			return new_node;
		}
	};

#if __cplusplus >= 201103L
	struct move_clone {
		node_alloc_type *node_alloc;

		move_clone(node_alloc_type &node_alloc_): node_alloc(&node_alloc_) {}
	
		link_type *operator ()(const link_type *link)
		{
			const node_type *node = static_cast<const link_type *>(link);
			node_type *new_node = node_alloc->allocate(1);
			try
			{
				allocator_type(*node_alloc).construct(new_node->valptr(), 
					std::move(*node->valptr()));
			}
			catch (...)
			{
				node_alloc->deallocate(new_node, 1);
				throw;
			}
			new_node->left = NULL;
			new_node->right = NULL;
			return new_node;
		}
	};
#endif // __cplusplus >= 201103L

	link_type *clone_node(const link_type *link)
	{
		return clone(node_alloc_).operator ()(link);
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
		bintree_init(&tree_);
	}

	void finalize()
	{
		bintree_destroy(&tree_, destroy(node_alloc_));
	}
};

} // namespace Hx

#endif // HX_MAP_H
