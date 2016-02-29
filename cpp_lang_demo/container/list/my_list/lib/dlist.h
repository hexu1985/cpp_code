#ifndef DLIST_H
#define DLIST_H

#include "dlist_base.h"

// 双向循环链表结点, 包含数据
template <typename T>
struct Dlist_node: public Dlist_node_base {
	T key;

	Dlist_node() {}
	Dlist_node(const T &k): key(k) {}
};

// 将Dlist_node_base类型的指针强制转换成Dlist_node类型的指针
template <typename T>
inline Dlist_node<T> *dlist_base2derived(Dlist_node_base *x)
{
	return static_cast<Dlist_node<T> *>(x);
}

// 获取下一结点指针
template <typename T>
inline Dlist_node<T> *dlist_next(Dlist_node<T> *x)
{
	return dlist_base2derived<T>(x->next);
}

// 获取前一结点指针
template <typename T>
inline Dlist_node<T> *dlist_prev(Dlist_node<T> *x)
{
	return dlist_base2derived<T>(x->prev);
}

// 获取双向循环链表结点包含数据的引用
template <typename T>
inline const T &dlist_key(Dlist_node_base *x)
{
	return dlist_base2derived<T>(x)->key;
}

// 搜索链表中第一个满足指定值的结点
template <typename T>
Dlist_node<T> *dlist_search(Dlist_node<T> *x, Dlist_node<T> *nil, const T &k)
{
	while (x != nil && x->key != k)
		x = dlist_next(x);
	return x;
}

// 搜索链表中第一个满足指定条件的结点
template <typename T, typename Pred>
Dlist_node<T> *dlist_search_if(Dlist_node<T> *x, Dlist_node<T> *nil, Pred pred)
{
	while (x != nil && !pred(x->key))
		x = dlist_next(x);
	return x;
}

// 排序链表中区间[a, b)的元素, 采用插入排序
// 区间至少包含一个结点
template <typename T>
void dlist_sort(Dlist_node<T> *a, Dlist_node<T> *b)
{
	if (a == b)	// 区间为空
		return;

	// 标识已序结束位置(已序元素最后一个元素的下一个元素的位置)
	Dlist_node<T> *i = dlist_next(a);
	for ( ; i != b; ) {
		Dlist_node<T> *k = dlist_next(i);	// 记录下i的一个元素位置
		Dlist_node<T> *j = i;
		for ( ; j != a; j = dlist_prev(j)) {	// 从右向左, 找到第一个小于或等于i的key的元素的位置
			if (i->key >= dlist_prev(j)->key)
				break;
		}
		if (i != j) {	// 将元素插入合适的位置
			dlist_delete(i);
			dlist_insert(j, i);
		}
		i = k;	// 更新已序结束位置
	}
}

// 排序链表中区间[a, b)的元素, 采用插入排序
// 区间至少包含一个结点
// 排序规则由comp来指定(comp 类似于 <)
template <typename T, typename Compare>
void dlist_sort(Dlist_node<T> *a, Dlist_node<T> *b, Compare comp)
{
	if (a == b)	// 区间为空
		return;

	// 标识已序结束位置(已序元素最后一个元素的下一个元素的位置)
	Dlist_node<T> *i = dlist_next(a);
	for ( ; i != b; ) {
		Dlist_node<T> *k = dlist_next(i);	// 记录下i的一个元素位置
		Dlist_node<T> *j = i;
		for ( ; j != a; j = dlist_prev(j)) {	// 从右向左, 找到第一个小于或等于i的key的元素的位置
			if (!comp(i->key, dlist_prev(j)->key))
				break;
		}
		if (i != j) {	// 将元素插入合适的位置
			dlist_delete(i);
			dlist_insert(j, i);
		}
		i = k;	// 更新已序结束位置
	}
}

// 双向循环链表:
// 无内存管理.
template <typename T>
class Dlist: public Dlist_base {
private:
	Dlist(const Dlist &);
	Dlist &operator =(const Dlist &);

public:
	Dlist() { dlist_init(this); }

	typedef Dlist_node<T> node_type;

	// 获取链表头结点的指针
	node_type *head()
	{
		return static_cast<node_type *>(dlist_head(this));
	}

	// 获取链表尾结点的指针
	node_type *tail()
	{
		return static_cast<node_type *>(dlist_tail(this)); 
	}

	// 获取指向链表哨兵节点nil的指针
	node_type *nil()
	{
		return static_cast<node_type *>(dlist_nil(this)); 
	}

	// 在链表的pos结点前插入new_node结点
	void insert(node_type *pos, node_type *new_node)
	{
		return dlist_insert(pos, new_node);
	}

	// 将[first, last]区间所包含结点插入链表的x结点前,
	// 区间至少包含一个结点
	void insert(node_type *pos, node_type *first, node_type *last)
	{
		return dlist_insert(pos, first, last);
	}

	// 在链表头插入结点
	void insert_head(node_type *new_node)
	{
		return dlist_insert(dlist_head(this), new_node);
	}

	// 在链表尾插入结点
	void insert_tail(node_type *new_node)
	{
		return dlist_insert(dlist_nil(this), new_node);
	}

	// 搜索链表中第一个满足指定值的结点
	node_type *find(const T &k)
	{
		return dlist_search(head(), nil(), k);
	}

	// 搜索链表中从pos开始第一个满足指定值的结点
	node_type *find(node_type *pos, const T &k)
	{
		return dlist_search(pos, nil(), k);
	}

	// 搜索链表中第一个满足指定条件的结点
	template <typename Pred>
	node_type *find_if(Pred pred)
	{
		return dlist_search_if(head(), nil(), pred);
	}

	// 搜索链表中从pos开始第一个满足指定条件的结点
	template <typename Pred>
	node_type *find_if(node_type *pos, Pred pred)
	{
		return dlist_search_if(pos, nil(), pred);
	}
	
	// 从链表上删除pos结点
	node_type *erase(node_type *pos)
	{
		node_type *tmp = dlist_next(pos);
		dlist_delete(pos);
		return tmp;
	}

	// 删除链表头结点
	node_type *erase_head()
	{
		node_type *tmp = head();
		dlist_delete(dlist_head(this));
		return tmp;
	}

	// 删除链表尾结点
	node_type *erase_tail()
	{
		node_type *tmp = tail();
		dlist_delete(dlist_tail(this));
		return tmp;
	}

	// 从链表中将[first, last]区间所包含结点删除,
	// 区间至少包含一个结点
	node_type *erase(node_type *first, node_type *last)
	{
		node_type *tmp = dlist_next(last);
		dlist_delete(first, last);
		return tmp;
	}

	// 获取链表中结点的个数
	int size()
	{
		return dlist_size(this);
	}

	// 判断list是否为空
	bool empty()
	{
		return dlist_empty(this);
	}

	// 交换两个链表中所有的结点
	void swap(Dlist &x)
	{
		dlist_swap(this, &x);
	}

	// 将另外一个链表所有结点插入到当前链表的pos结点前
	void splice(node_type *pos, Dlist &x)
	{
		if (x.empty())
			return;

		dlist_transfer(pos, dlist_head(&x), dlist_tail(&x));
	}

	// 将另外一个链表的node结点插入到当前链表的pos结点前
	void splice(node_type *pos, Dlist &x, node_type *node)
	{
		x.erase(node);
		this->insert(pos, node);	
	}

	// 将另外一个链表的[first, last]区间所包含结点插入到当前链表的pos结点前
	void splice(node_type *pos, Dlist &x, node_type *first, node_type *last)
	{
		dlist_transfer(pos, first, last);
	}

	// 将整个链表逆序
	void reverse()
	{
		dlist_reverse(this);
	}

	// 排序整个链表
	void sort()
	{
		dlist_sort(this->head(), this->nil());
	}

	template <typename Compare>
	void sort(Compare comp)
	{
		dlist_sort(this->head(), this->nil(), comp);
	}
};

#endif
