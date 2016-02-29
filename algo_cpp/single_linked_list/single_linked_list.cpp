// -*- C++ -*-
// HeXu's
// 2013 Dec

#include "single_linked_list.h"

namespace Hx {
namespace single_linked {

/**
 * 初始化链表
 *
 * [head] -> NIL
 */
void list_init(list_t *list)
{
	list->head.next = NULL;
}

// 判断list是否为空, 
// 如果为空返回true,
// 否则返回false
bool list_empty(const list_t *list)
{
	return (list->head.next == NULL);
}

/**
 * 获取链表头结点的地址
 *
 * [head] -> [N1] -> [N2] -> ... -> NIL
 *             ^head
 */
list_node_t *list_head(list_t *list)
{
	return list->head.next;
}

/**
 * 获取链表逾头结点位置地址
 *
 * [head] -> [N1] -> [N2] -> ... -> NIL
 *   ^        ^head
 *   ^under_head 
 */
list_node_t *list_under_head(list_t *list)
{
	return &list->head;
}

/**
 * 获取链表尾结点的地址
 *
 * [head] -> [N1] -> [N2] -> ... -> [Nk] -> NIL
 *                                    ^tail
 */
list_node_t *list_tail(list_node_t *x)
{
	list_node_t *y = NULL;		// y keep x->prev
	while (x != NULL) {
		y = x;
		x = x->next;
	}
	return y;
}

// 获取链表尾结点的地址
list_node_t *list_tail(list_t *list)
{
	return list_tail(&list->head);
}

/**
 * 在链表的x结点后插入y结点
 *            ___                ___
 *    ------>|   |------------->|   |------>
 *           |___|              |___|
 *             ^-x
 *                     ___        
 *                    |   |------>
 *                    |___|       
 *                      ^-y       
 * =========================================
 *            ___                ___
 *    ------>|   |------------->|   |------>
 *           |___|          .-->|___|
 *             ^-x          |
 *                     ___  |      
 *                    |   |-'
 *                    |___|       
 *                      ^-y       
 * =========================================
 *            ___                ___
 *    ------>|   |--.        .->|   |------>
 *           |___|  |        |  |___|
 *             ^-x  |        |
 *                  |   ___  |      
 *                  '->|   |-'
 *                     |___|       
 *                       ^-y       
 */
void list_insert_after(list_node_t *x, list_node_t *y)
{
	y->next = x->next;
	x->next = y;
}

// 将[a, b]区间所包含结点插入链表的x结点后,
// 区间至少包含一个结点
void list_insert_after(list_node_t *x, list_node_t *a, list_node_t *b)
{
	// 如果b为NIL, 设置b为通过a找到的list tail
	if (b == NULL) {
		b = list_tail(a);
	}

	b->next = x->next;
	x->next = a;
}

// 在链表头插入结点
void list_insert_head(list_t *list, list_node_t *x)
{
	list_insert_after(list_under_head(list), x);
}

/**
 * 从链表上删除x结点后面的结点
 *            ___           ___           ___ 
 *    ------>|   |-------->|   |-------->|   |------>
 *           |___|         |___|         |___|
 *             ^-x           ^-y      
 * ==================================================
 *                     ____________________
 *                    |                    |
 *            ___     |     ___           _V_ 
 *    ------>|   |----'    |   |-------->|   |------>
 *           |___|         |___|         |___|
 *             ^-x           ^-y
 */
void list_remove_after(list_node_t *x)
{
	list_node_t *y = x->next;
	if (y != NULL) {
		x->next = y->next;
	}
}

// 从链表中将(a, b]区间所包含结点删除,
// 如果有结点被删除, 返回被删除区间的第一个结点, 即a->next
void list_remove_after(list_node_t *a, list_node_t *b)
{
	if (a == b)	// 判断(a, b]是否为空
		return;

	// 如果b为NIL, 则说明删除a->next到tail的所有结点
	a->next = (b == NULL ? NULL : b->next);
}

// 在链表头插入结点
void list_remove_head(list_t *list)
{
	list_remove_after(list_under_head(list));
}

// 将另外一个链表的(a, b]区间所包含结点插入到
// 当前链表的x结点后,
// 并且还要保持另外一个链表为有效链表
void list_transfer_after(list_node_t *x, list_node_t *a, list_node_t *b)
{
	if (a == b || a->next == b)
		return;

	list_node_t *c = a->next;	// keep c = a->next
	list_remove_after(a, b);
	list_insert_after(x, c, b);
}

// 反转链表中区间(a, b)包含结点的顺序,
// 区间至少包含一个结点
void list_reverse_after(list_node_t *a, list_node_t *b)
{
	if (a == b || a->next == b)
		return;

	list_node_t *c = a->next;
	list_node_t *d = c->next;
	for ( ; d != b; d = c->next) {
		list_remove_after(c);
		list_insert_after(a, d);
	}
}

// 将整个链表逆序
void list_reverse(list_t *list)
{
	list_reverse_after(list_under_head(list), NULL);
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
	return list_size(list->head.next, NULL);
}

// 交换两个链表中所有的结点,
// 保持结点间原有的顺序
void list_swap(list_t *a, list_t *b)
{
	list_node_t tmp = a->head;
	a->head = b->head;
	b->head = tmp;
}

} // namespace single_linked
} // namespace Hx

