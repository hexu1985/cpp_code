// -*- C++ -*-
// HeXu's
// 2013 Dec

#ifndef __single_linked_list_h
#define __single_linked_list_h

#include <stddef.h>

namespace Hx {
namespace single_linked {

// 单向链表结点, 不包含数据
typedef struct list_node_t {
	struct list_node_t *next;
} list_node_t;

// 带头结点的单向链表
typedef struct list_t {
	list_node_t head;
} list_t;

// 初始化链表
void list_init(list_t *list);

// 判断list是否为空, 
// 如果为空返回true,
// 否则返回false
bool list_empty(const list_t *list);

// 获取链表头结点的地址
list_node_t *list_head(list_t *list);

// 获取链表逾头结点位置地址
list_node_t *list_under_head(list_t *list);

// 获取链表尾结点的地址
list_node_t *list_tail(list_node_t *x);

// 获取链表尾结点的地址
list_node_t *list_tail(list_t *list);

// 在链表的x结点后插入y结点
void list_insert_after(list_node_t *x, list_node_t *y);

// 将[a, b]区间所包含结点插入链表的x结点后,
// 区间至少包含一个结点
void list_insert_after(list_node_t *x, list_node_t *a, list_node_t *b);

// 在链表头插入结点
void list_insert_head(list_t *list, list_node_t *x);

// 从链表上删除x结点后面的结点
void list_remove_after(list_node_t *x);

// 从链表中将(a, b]区间所包含结点删除,
// 如果有结点被删除, 返回被删除区间的第一个结点, 即a->next
void list_remove_after(list_node_t *a, list_node_t *b);

// 在链表头插入结点
void list_remove_head(list_t *list);

// 将另外一个链表的(a, b]区间所包含结点插入到
// 当前链表的x结点后,
// 并且还要保持另外一个链表为有效链表
void list_transfer_after(list_node_t *x, list_node_t *a, list_node_t *b);

// 反转链表中区间(a, b)包含结点的顺序,
// 区间至少包含一个结点
void list_reverse_after(list_node_t *a, list_node_t *b);

// 将整个链表逆序
void list_reverse(list_t *list);

// 获取链表中[a, b)区间包含结点的个数,
size_t list_size(list_node_t *a, list_node_t *b);

// 获取链表中结点的个数
size_t list_size(list_t *list);

// 交换两个链表中所有的结点,
// 保持结点间原有的顺序
void list_swap(list_t *a, list_t *b);

} // namespace single_linked
} // namespace Hx

#endif // __single_linked_list_h

