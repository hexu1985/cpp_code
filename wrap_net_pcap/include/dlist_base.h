// -*- C++ -*-
// HeXu's
// 2015 Apr

#ifndef DLIST_BASE_H
#define DLIST_BASE_H

// 双向循环链表结点的基类, 不包含数据
struct Dlist_node_base {
	Dlist_node_base *next;
	Dlist_node_base *prev;
};

// 带哨兵结点的双向循环链表
struct Dlist_base {
	Dlist_node_base nil;	// 哨兵结点
};

// 获取指向链表哨兵节点nil的指针
Dlist_node_base *dlist_nil(Dlist_base *list);

// 初始化链表
void dlist_nil_init(Dlist_node_base *x);
void dlist_init(Dlist_base *list);

// 判断list是否为空, 
// 如果为空返回true,
// 否则返回false
bool dlist_empty(Dlist_base *list);

// 获取链表头结点的指针
Dlist_node_base *dlist_head(Dlist_base *list);

// 获取链表尾结点的指针
Dlist_node_base *dlist_tail(Dlist_base *list);

// 在链表的x结点前插入y结点
void dlist_insert(Dlist_node_base *x, Dlist_node_base *y);

// 将[a, b]区间所包含结点插入链表的x结点前,
// 区间至少包含一个结点
void dlist_insert(Dlist_node_base *x, Dlist_node_base *a, Dlist_node_base *b);

// 从链表上删除x结点
void dlist_delete(Dlist_node_base *x);

// 从链表中将[a, b]区间所包含结点删除,
// 区间至少包含一个结点
void dlist_delete(Dlist_node_base *a, Dlist_node_base *b);

// 将另外一个链表的[a, b]区间所包含结点插入到
// 当前链表的x结点前,
// 并且还要保持另外一个链表为有效链表,
// 区间至少包含一个结点
void dlist_transfer(Dlist_node_base *x, Dlist_node_base *a, Dlist_node_base *b);

// 反转链表中区间[a, b)包含结点的顺序,
// 区间至少包含一个结点
void dlist_reverse(Dlist_node_base *a, Dlist_node_base *b);

// 将整个链表逆序
void dlist_reverse(Dlist_base *list);

// 获取链表中[a, b]区间包含结点的个数,
// 区间至少包含一个结点
int dlist_size(Dlist_node_base *a, Dlist_node_base *b);

// 获取链表中结点的个数
int dlist_size(Dlist_base *list);

// 交换两个链表中所有的结点,
// 保持结点间原有的顺序
void dlist_swap(Dlist_base *x, Dlist_base *y);

#endif // __double_linked_list_h

