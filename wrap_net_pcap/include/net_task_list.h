#ifndef NET_TASK_LIST_H
#define NET_TASK_LIST_H

#include "dlist_base.h"

// 双向循环链表结点, 包含数据
template <typename T>
struct Net_task_node: public Dlist_node_base {
	T task;

	Net_task_node() {}
	Net_task_node(const T &t): task(t) {}
};

// 将Dlist_node_base类型的指针强制转换成Net_task_node类型的指针
template <typename T>
inline Net_task_node<T> *dlist_base2derived(Dlist_node_base *x)
{
	return static_cast<Net_task_node<T> *>(x);
}

// 获取下一结点指针
template <typename T>
inline Net_task_node<T> *dlist_next(Net_task_node<T> *x)
{
	return dlist_base2derived<T>(x->next);
}

// 获取前一结点指针
template <typename T>
inline Net_task_node<T> *dlist_prev(Net_task_node<T> *x)
{
	return dlist_base2derived<T>(x->prev);
}

template <typename T>
class Net_task_list: public Dlist_base {
private:
	Net_task_list(const Net_task_list &);
	Net_task_list &operator =(const Net_task_list &);

public:
	Net_task_list() { dlist_init(this); }

	typedef Net_task_node<T> node_type;

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

	// 在链表的pos结点前插入new_task结点
	void insert(node_type *pos, node_type *new_task)
	{
		return dlist_insert(pos, new_task);
	}

	// 将[first, last]区间所包含结点插入链表的x结点前,
	// 区间至少包含一个结点
	void insert(node_type *pos, node_type *first, node_type *last)
	{
		return dlist_insert(pos, first, last);
	}

	// 在链表头插入结点
	void insert_head(node_type *new_task)
	{
		return dlist_insert(dlist_head(this), new_task);
	}

	// 在链表尾插入结点
	void insert_tail(node_type *new_task)
	{
		return dlist_insert(dlist_nil(this), new_task);
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
	void swap(Net_task_list &x)
	{
		dlist_swap(this, &x);
	}

	// 将另外一个链表所有结点插入到当前链表的pos结点前
	void splice(node_type *pos, Net_task_list &x)
	{
		if (x.empty())
			return;

		dlist_transfer(pos, dlist_head(&x), dlist_tail(&x));
	}

	// 将另外一个链表的task结点插入到当前链表的pos结点前
	void splice(node_type *pos, Net_task_list &x, node_type *task)
	{
		x.erase(task);
		this->insert(pos, task);	
	}

	// 将另外一个链表的[first, last]区间所包含结点插入到当前链表的pos结点前
	void splice(node_type *pos, Net_task_list &x, node_type *first, node_type *last)
	{
		dlist_transfer(pos, first, last);
	}

	// 将整个链表逆序
	void reverse()
	{
		dlist_reverse(this);
	}
};

#endif
