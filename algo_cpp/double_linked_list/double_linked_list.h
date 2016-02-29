// -*- C++ -*-
// HeXu's
// 2015 Apr

#ifndef __double_linked_list_h
#define __double_linked_list_h

#include <stddef.h>

namespace Hx {
namespace double_linked {

// 双向循环链表结点, 不包含数据
typedef struct list_node_t {
	struct list_node_t *next;
	struct list_node_t *prev;
} list_node_t;

// 带哨兵结点的双向循环链表
typedef struct list_t {
	list_node_t *nil;	// 哨兵结点
} list_t;

// 初始化链表
void list_init(list_t *list);
void list_init(list_t *list, list_node_t *nil);

// 判断list是否为空, 
// 如果为空返回true,
// 否则返回false
bool list_empty(list_t *list);

// 获取链表头结点的地址
list_node_t *list_head(list_t *list);

// 获取链表尾结点的地址
list_node_t *list_tail(list_t *list);

// 获取链表逾尾结点的地址
list_node_t *list_over_tail(list_t *list);

// 在链表的x结点前插入y结点
void list_insert(list_node_t *x, list_node_t *y);

// 将[a, b]区间所包含结点插入链表的x结点前,
// 区间至少包含一个结点
void list_insert(list_node_t *x, list_node_t *a, list_node_t *b);

// 从链表上删除x结点
void list_remove(list_node_t *x);

// 从链表中将[a, b]区间所包含结点删除,
// 区间至少包含一个结点
void list_remove(list_node_t *a, list_node_t *b);

// 将另外一个链表的[a, b]区间所包含结点插入到
// 当前链表的x结点前,
// 并且还要保持另外一个链表为有效链表,
// 区间至少包含一个结点
void list_transfer(list_node_t *x, list_node_t *a, list_node_t *b);

// 反转链表中区间[a, b]包含结点的顺序,
// 区间至少包含一个结点
void list_reverse(list_node_t *a, list_node_t *b);

// 将整个链表逆序
void list_reverse(list_t *list);

// 获取链表中[a, b]区间包含结点的个数,
// 区间至少包含一个结点
size_t list_size(list_node_t *a, list_node_t *b);

// 获取链表中结点的个数
size_t list_size(list_t *list);

// 交换两个链表中所有的结点,
// 保持结点间原有的顺序
void list_swap(list_t *x, list_t *y);

} // namespace double_linked
} // namespace Hx

#endif // __double_linked_list_h

