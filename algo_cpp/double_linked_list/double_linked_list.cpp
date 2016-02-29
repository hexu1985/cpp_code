// -*- C++ -*-
// HeXu's
// 2015 Apr

#include <assert.h>
#include "double_linked_list.h"

namespace Hx {
namespace double_linked {

/**
 * 初始化链表
 *         ____
 *        |    |
 *        V    |
 *   .--[nil]--'
 *   |    A    
 *   |____|     
 */
inline void list_init_nil(list_node_t *x)
{
	assert(x);
	// 初始化nil结点
	x->next = x;
	x->prev = x;
}

void list_init(list_t *list)
{
	list_init_nil(list->nil);
}

void list_init(list_t *list, list_node_t *nil)
{
	list_init_nil(nil);
	list->nil = nil;
}

// 判断list是否为空, 
// 如果为空返回true,
// 否则返回false
bool list_empty(list_t *list)
{
	return (list->nil->next == list->nil);
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
list_node_t *list_head(list_t *list)
{
	return list->nil->next;
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
list_node_t *list_tail(list_t *list)
{
	return list->nil->prev;
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
list_node_t *list_over_tail(list_t *list)
{
	return list->nil;
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
void list_insert(list_node_t *x, list_node_t *y)
{
	y->prev = x->prev;
	y->next = x;
	x->prev->next = y;
	x->prev = y;
}

// 将[a, b]区间所包含结点插入链表的x结点前,
// 区间至少包含一个结点
void list_insert(list_node_t *x, list_node_t *a, list_node_t *b)
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
void list_remove(list_node_t *x)
{
	x->prev->next = x->next;
	x->next->prev = x->prev;
}

// 从链表中将[a, b]区间所包含结点删除,
// 区间至少包含一个结点
void list_remove(list_node_t *a, list_node_t *b)
{
	a->prev->next = b->next;
	b->next->prev = a->prev;
}

// 将另外一个链表的[a, b]区间所包含结点插入到
// 当前链表的x结点前,
// 并且还要保持另外一个链表为有效链表,
// 区间至少包含一个结点
void list_transfer(list_node_t *x, list_node_t *a, list_node_t *b)
{
	list_remove(a, b);
	list_insert(x, a, b);
}

// 反转链表中区间[a, b)包含结点的顺序,
// 区间至少包含一个结点
void list_reverse(list_node_t *a, list_node_t *b)
{
	if (a == b)	// 区间只包含一个结点, 不需要排序
		return;

	// b结点的前一结点开始, 到a结点结束(不包括a结点),
	// 将依次遍历的结点插入到a结点前
	for (list_node_t *c = b->prev; c != a; c = b->prev) {
		list_remove(c);
		list_insert(a, c);
	}
}

// 将整个链表逆序
void list_reverse(list_t *list)
{
	list_reverse(list_head(list), list_over_tail(list));
}

// 获取链表中[a, b)区间包含结点的个数,
size_t list_size(list_node_t *a, list_node_t *b)
{
	size_t n = 0;
	while (a != b) {
		a = a->next;
		n++;
	}
	return n;
}

// 获取链表中结点的个数
size_t list_size(list_t *list)
{
	return list_size(list_head(list), list_over_tail(list));
}

// 交换两个链表中所有的结点,
// 保持结点间原有的顺序
void list_swap(list_t *x, list_t *y)
{
	list_node_t *tmp = x->nil;
	x->nil = y->nil;
	y->nil = tmp;
}

} // namespace double_linked
} // namespace Hx

