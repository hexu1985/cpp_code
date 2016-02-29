#ifndef __test_single_linked_list_h
#define __test_single_linked_list_h

#include <iostream>
#include <string>
#include <stdexcept>

#include "single_linked_list.h"

using namespace Hx::single_linked;

template <typename T>
struct List_node: public list_node_t {
	T key;

	List_node() {}
	List_node(const T &key_): key(key_) {}
};

template <typename T>
struct List_iterator {
	list_node_t *link;

	typedef list_node_t link_type;
	typedef List_node<T> node_type;
	typedef List_iterator self_type;
	typedef	std::forward_iterator_tag iterator_category;

	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef T *pointer;
	typedef T &reference;

	List_iterator() {}
	List_iterator(link_type *link_): link(link_) {}

	T &operator *() const	// 解引用
	{
		return static_cast<node_type *>(link)->key;
	}

	T *operator ->() const
	{
		return &static_cast<node_type *>(link)->key;
	}

	self_type &operator ++()	// ++i
	{
		link = link->next;
		return *this;
	}

	self_type operator ++(int)	// i++
	{
		self_type tmp(*this);
		link = link->next;
		return tmp;
	}

	bool operator ==(const self_type &x)
	{
		return link == x.link;
	}

	bool operator !=(const self_type &x)
	{
		return !(*this == x);
	}
};

template <typename T>
class List: public list_t {
public:
	typedef list_node_t link_type;
	typedef List_node<T> node_type;
	typedef	List_iterator<T> iterator;
	typedef List self_type;

	inline static self_type *remove_const(const self_type *ptr)
	{
		return const_cast<self_type *>(ptr);
	}

	List() { list_init(this); }

	~List() { clear(); }

	List(const List &x)
	{
		list_init(this);
		link_type *link = list_head(remove_const(&x));
		link_type *tail = list_tail(this);
		for ( ; link != NULL; link = link->next, tail = tail->next) {
			node_type *node = static_cast<node_type *>(link);
			list_insert_after(tail, new node_type(node));
		}
	}

#if __cplusplus >= 201103L
	List(List &&x)
	{
	}
#endif

	bool empty() const { return list_empty(remove_const(this)); }

	size_t size() const { return list_size(remove_const(this)); }

	iterator begin() const
	{
		return iterator(list_head(remove_const(this))); 
	}

	iterator before_begin() const
	{
		return iterator(list_under_head(remove_const(this)));
	}

	iterator end() const
	{
		return iterator(NULL); 
	}

	void push_front(const T &k) 
	{
		node_type *node = new node_type(k);
		list_insert_head(this, node);
	}

	void pop_front()
	{
		if (empty())
			throw std::underflow_error("pop_front error: list is empty!");

		node_type *node = static_cast<node_type *>(list_head(this));
		list_remove_head(this);
		delete node;
	}

	const T &front() const
	{
		if (empty())
			throw std::runtime_error("front error: list is empty!");

		node_type *node = static_cast<node_type *>(list_head(this));
		return node->key;
	}

	T &front()
	{
		if (empty())
			throw std::underflow_error("front error: list is empty!");

		node_type *node = static_cast<node_type *>(list_head(this));
		return node->key;
	}

	iterator find(const T &k)
	{
		link_type *link = list_head(this);
		for ( ; link != NULL; link = link->next) {
			node_type *node = static_cast<node_type *>(link);
			if (node->key == k)
				return iterator(node);
		}
		return end();
	}

	void remove(const T &k)
	{
		link_type *link = list_head(this);
		link_type *keep = list_under_head(this);
		while (link != NULL) {
			node_type *node = static_cast<node_type *>(link);
			if (node->key == k) {
				list_remove_after(keep);
				delete node;
				link = keep->next;
			} else {
				keep = keep->next;
				link = link->next;
			}
		}
	}

	iterator insert_after(iterator x, const T &k)
	{
		node_type *node = new node_type(k);
		list_insert_after(x.link, node);
		return iterator(node);
	}

	void erase_after(iterator x)
	{
		link_type *keep = x.link->next;
		list_remove_after(x.link);
		delete static_cast<node_type *>(keep);
	}

	void splice_after(iterator x, List &list)
	{
		if (list.empty())
			return;

		list_transfer_after(x.link, list_under_head(&list), NULL);
	}

	void swap(List &list)
	{
		list_swap(this, &list);
	}

	void clear()
	{
		link_type *link = list_head(this);
		while (link != NULL) {
			node_type *node = static_cast<node_type *>(link);
			link = link->next;
			delete node;
		}
		list_init(this);
	}

	void reverse()
	{
		list_reverse(this);
	}

#if 0
	bool is_sorted() const
	{
		return true;
	}

	void insert_sort()
	{
	}

	void quick_sort()
	{
	}

	void unique()
	{
	}

	void merge(List &list)
	{
	}
#endif
};

#endif
