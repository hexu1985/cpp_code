// -*- C++ -*-
// HeXu's
// 2015 Apr

#include <assert.h>
#include "dlist_base.h"

/**
 * 获取链表哨兵节点nil的指针
 *        __________________________________________________
 *       |                                                  |
 *       V                                                  |
 *   .--[N4] <=> [N5] <=> [nil] <=> [N1] <=> [N2] <=> [N3]--'
 *   |                                                 A
 *   |_________________________________________________|
 */
inline Dlist_node_base *dlist_nil(Dlist_base *list)
{
	return &list->nil;
}

/**
 * 初始化链表
 *         ____
 *        |    |
 *        V    |
 *   .--[nil]--'
 *   |    A    
 *   |____|     
 */
inline void dlist_nil_init(Dlist_node_base *x)
{
	assert(x);
	// 初始化nil结点
	x->next = x;
	x->prev = x;
}

void dlist_init(Dlist_base *list)
{
	dlist_nil_init(dlist_nil(list));
}

// 判断list是否为空, 
// 如果为空返回true,
// 否则返回false
bool dlist_empty(Dlist_base *list)
{
	Dlist_node_base *nil = dlist_nil(list);
	return (nil->next == nil);
}

/**
 * 获取链表头结点的地址
 *        __________________________________________________
 *       |                                                  |
 *       V                                                  |
 *   .--[N4] <=> [N5] <=> [nil] <=> [N1] <=> [N2] <=> [N3]--'
 *   |                               ^-head            A
 *   |_________________________________________________|
 */
Dlist_node_base *dlist_head(Dlist_base *list)
{
	return dlist_nil(list)->next;
}

/**
 * 获取链表尾结点的地址
 *        __________________________________________________
 *       |                                                  |
 *       V                                                  |
 *   .--[N4] <=> [N5] <=> [nil] <=> [N1] <=> [N2] <=> [N3]--'
 *   |            ^-tail                               A
 *   |_________________________________________________|
 */
Dlist_node_base *dlist_tail(Dlist_base *list)
{
	return dlist_nil(list)->prev;
}

/**
 * 获取链表逾尾结点的地址
 *        __________________________________________________
 *       |                                                  |
 *       V                                                  |
 *   .--[N4] <=> [N5] <=> [nil] <=> [N1] <=> [N2] <=> [N3]--'
 *   |                      ^-over_tail                A
 *   |_________________________________________________|
 */
Dlist_node_base *dlist_over_tail(Dlist_base *list)
{
	return dlist_nil(list);
}

/**
 * 在链表的x结点前插入y结点
 *            ___                ___
 *           |   |------------->|   |------>
 *    <------|___|<-------------|___|
 *                                ^-x
 *                  ___        
 *                 |   |------>
 *            <----|___|       
 *                   ^-y       
 * =========================================
 *            ___                ___
 *           |   |------------->|   |------>
 *    <------|___|<-------------|___|
 *             A                 A ^-x
 *             |    ___          |
 *             |   |   |---------'
 *             '---|___|       
 *                   ^-y       
 * =========================================
 *            ___                ___
 *           |   |--.     .---->|   |------>
 *    <------|___|  |     |  .--|___|
 *             A    |     |  |    ^-x
 *             |    V__   |  |
 *             |   |   |--'  |
 *             '---|___|<----'
 *                   ^-y
 */
inline void dlist_insert(Dlist_node_base *x, Dlist_node_base *y)
{
	y->prev = x->prev;
	y->next = x;
	x->prev->next = y;
	x->prev = y;
}

// 将[a, b]区间所包含结点插入链表的x结点前,
// 区间至少包含一个结点
inline void dlist_insert(Dlist_node_base *x, Dlist_node_base *a, Dlist_node_base *b)
{
	a->prev = x->prev;
	b->next = x;
	x->prev->next = a;
	x->prev = b;
}

/**
 * 从链表上删除x结点
 *            ___           ___           ___ 
 *           |   |-------->|   |-------->|   |------>
 *    <------|___|<--------|___|<--------|___|
 *                           ^-x       
 * ==================================================
 *                     ____________________
 *                    |                    |
 *            ___     |     ___           _V_ 
 *           |   |----'    |   |-------->|   |------>
 *    <------|___|<--------|___|    .----|___|
 *             A             ^-x    |   
 *             |____________________|                    
 */
inline void dlist_delete(Dlist_node_base *x)
{
	x->prev->next = x->next;
	x->next->prev = x->prev;
}

// 从链表中将[a, b]区间所包含结点删除,
// 区间至少包含一个结点
inline void dlist_delete(Dlist_node_base *a, Dlist_node_base *b)
{
	a->prev->next = b->next;
	b->next->prev = a->prev;
}

// 将另外一个链表的[a, b]区间所包含结点插入到
// 当前链表的x结点前,
// 并且还要保持另外一个链表为有效链表,
// 区间至少包含一个结点
void dlist_transfer(Dlist_node_base *x, Dlist_node_base *a, Dlist_node_base *b)
{
	dlist_delete(a, b);
	dlist_insert(x, a, b);
}

// 反转链表中区间[a, b)包含结点的顺序,
// 区间至少包含一个结点
void dlist_reverse(Dlist_node_base *a, Dlist_node_base *b)
{
	if (a == b)	// 区间为空
		return;

	// b结点的前一结点开始, 到a结点结束(不包括a结点),
	// 将依次遍历的结点插入到a结点前
	for (Dlist_node_base *c = b->prev; c != a; c = b->prev) {
		dlist_delete(c);
		dlist_insert(a, c);
	}
}

// 将整个链表逆序
void dlist_reverse(Dlist_base *list)
{
	dlist_reverse(dlist_head(list), dlist_nil(list));
}

// 获取链表中[a, b)区间包含结点的个数,
int dlist_size(Dlist_node_base *a, Dlist_node_base *b)
{
	int n = 0;
	while (a != b) {
		a = a->next;
		n++;
	}
	return n;
}

// 获取链表中结点的个数
int dlist_size(Dlist_base *list)
{
	return dlist_size(dlist_head(list), dlist_nil(list));
}

// 交换两个链表中所有的结点,
// 保持结点间原有的顺序
void dlist_swap(Dlist_base *x, Dlist_base *y)
{
	Dlist_base tmp;
	Dlist_base *z = &tmp;
	dlist_init(z);
	dlist_transfer(dlist_nil(z), dlist_head(x), dlist_tail(x));
	dlist_transfer(dlist_nil(x), dlist_head(y), dlist_tail(y));
	dlist_transfer(dlist_nil(y), dlist_head(z), dlist_tail(z));
}

