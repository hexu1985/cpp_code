#ifndef __test_double_linked_list_h
#define __test_double_linked_list_h

#include <iostream>
#include <string>
#include <stdexcept>

#include "double_linked_list.h"

using namespace Hx::double_linked;

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
	typedef	std::bidirectional_iterator_tag iterator_category;

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

	self_type &operator --()	// --i
	{
		link = link->prev;
		return *this;
	}

	self_type operator --(int)	// i--
	{
		self_type tmp(*this);
		link = link->prev;
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

	List() { list_init(this, new link_type); }

	~List() 
	{
		list_destroy(this);
	   	delete this->nil;
	}

	bool empty() const { return list_empty(remove_const(this)); }

	size_t size() const { return list_size(remove_const(this)); }

	iterator begin() const
	{
		return iterator(list_head(remove_const(this))); 
	}

	iterator end() const
	{
		return iterator(list_over_tail(remove_const(this))); 
	}

	void push_front(const T &k) 
	{
		node_type *node = new node_type(k);
		list_insert(list_head(this), node);
	}

	void push_back(const T &k)
	{
		node_type *node = new node_type(k);
		list_insert(list_over_tail(this), node);
	}

	void pop_front()
	{
		if (empty())
			throw std::underflow_error("pop_front error: list is empty!");

		node_type *node = static_cast<node_type *>(list_head(this));
		list_remove(node);
		delete node;
	}

	void pop_back()
	{
		if (empty())
			throw std::underflow_error("pop_back error: list is empty!");

		node_type *node = static_cast<node_type *>(list_tail(this));
		list_remove(node);
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
			throw std::runtime_error("front error: list is empty!");

		node_type *node = static_cast<node_type *>(list_head(this));
		return node->key;
	}

	const T &back() const
	{
		if (empty())
			throw std::underflow_error("back error: list is empty!");

		node_type *node = static_cast<node_type *>(list_tail(this));
		return node->key;
	}

	T &back()
	{
		if (empty())
			throw std::underflow_error("back error: list is empty!");

		node_type *node = static_cast<node_type *>(list_tail(this));
		return node->key;
	}

	iterator find(const T &k) const
	{
		return list_search(remove_const(this), k);
	}

	iterator insert(iterator x, const T &k)
	{
		node_type *node = new node_type(k);
		list_insert(x.link, node);
		return iterator(node);
	}

	void erase(iterator x)
	{
		list_remove(x.link);
		delete static_cast<node_type *>(x.link);
	}

	void splice(iterator x, List &list)
	{
		if (list.empty())
			return;

		list_transfer(x.link, list_head(&list), list_tail(&list));
	}

	void swap(List &list)
	{
		list_swap(this, &list);
	}

	void clear()
	{
		list_destroy(this);
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

private:
	static void list_destroy(list_t *list)
	{
		list_destroy(list_head(list), list_over_tail(list));
	}

	// 对[first, last)区间的list结点指针调用delete
	static void list_destroy(link_type *first, link_type *last)
	{
		while (first != last) {
			node_type *node = static_cast<node_type *>(first);
			first = first->next;
			delete node;
		}
	}

	static link_type *list_search(list_t *list, const T &key)
	{
		return list_search(list_head(list), list_over_tail(list), key);
	}

	// 查找[first, last)区间中值等于key的结点, 并返回指针,
	// 如果找不到则返回last
	static link_type *list_search(link_type *first, link_type *last, const T &key)
	{
		for ( ; first != last; first = first->next) {
			if (static_cast<node_type *>(first)->key == key)
				break;
		}
		return first;
	}
};

#endif
