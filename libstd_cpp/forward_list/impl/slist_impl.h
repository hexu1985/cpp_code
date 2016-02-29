// -*- C++ -*-
// HeXu's
// 2013 Dec

#ifndef HX_SLIST_IMPL_H
#define HX_SLIST_IMPL_H

#ifdef __cplusplus
#include <cstddef>
#include <cassert>
#else
#include <stddef.h>
#include <assert.h>
#endif // __cplusplus

#ifdef __cplusplus
namespace Hx {
namespace detail {
#endif // __cplusplus

/**
 * Singly linked list node 
 */
typedef struct slist_node_t {
	struct slist_node_t *next;
} slist_node_t;

/**
 * Singly linked list
 */
typedef struct slist_t {
	slist_node_t head;
} slist_t;

/**
 * initialize singly linked list
 * [head] -> [NIL]
 */
inline
void slist_init(slist_t *lst)
{
	lst->head.next = NULL;
}

/**
 * get list first node link
 */
inline
slist_node_t *slist_head(const slist_t *lst)
{
	return (slist_node_t *) lst->head.next;
}

/**
 * get list before first node link
 */
inline
slist_node_t *slist_before_head(const slist_t *lst)
{
	return (slist_node_t *) &lst->head;
}

/**
 * test if list is empty
 */
inline
int slist_is_empty(const slist_t *lst)
{
	return (lst->head.next == NULL);
}

/**
 * insert a node after this node
 * [head] -> [N1] -> [N2] -> [N3] -> [...] -> [NIL]
 *                     ^-pos
 *                 ||
 *                 \/
 * [head] -> [N1] -> [N2] -> [M] -> [N3] -> [...] -> [NIL]
 *                     ^-pos  ^-node  
 */
inline
void slist_insert_after(slist_node_t *pos, slist_node_t *node)
{
	node->next = pos->next;
	pos->next = node;
}

/**
 * remove node after pos node from list
 * [head] -> [N1] -> [N2] -> [N3] -> [N4] -> [...] -> [NIL]
 *                     ^-pos   ^-keep
 *                  ||
 *                  \/
 * [head] -> [N1] -> [N2] -> [N4] -> [...] -> [NIL]
 *                     ^-pos
 */
inline
slist_node_t *slist_remove_after(slist_node_t *pos)
{
	slist_node_t *keep = pos->next;
	if (keep != NULL)
		pos->next = keep->next;	
	return keep;
}

/**
 * remove node range (pos, last)
 * [...] -> [N1] -> [N2] -> [N3] -> [N4] -> [N5] -> [N6] -> [...]
 *                    ^-pos                   ^-last
 *                  ||
 *                  \/
 * [...] -> [N1] -> [N2] -> [N6] -> [...]
 *                    ^-pos   
 */
inline
slist_node_t *slist_range_remove_after(slist_node_t *pos, slist_node_t *last)
{
	slist_node_t *keep = pos;
	if (pos == last || (pos = pos->next) == last)
		return NULL;
	keep->next = last;
	return pos;
}

/**
 * get number of elements in list
 */
inline
size_t slist_size(const slist_t *lst)
{
	size_t n = 0;
	slist_node_t *node = lst->head.next;
	while (node != NULL) {
		node = node->next;
		n++;
	}
	return n;
}

/**
 * swap two list
 */
inline
void slist_swap(slist_t *a, slist_t *b)
{
	slist_node_t temp = a->head;
	a->head = b->head;
	b->head = temp;
}

/**
 * get previous node 
 */
inline
slist_node_t *slist_get_prev(const slist_node_t *head, 
	const slist_node_t *node)
{
	assert(head != NULL);

	const slist_node_t *keep = head;
	while ((keep->next != node) && (keep->next != NULL)) 
		keep = keep->next;
	return (slist_node_t *) keep;
}

/**
 * transfer (first, last) after this node
 * [...] -> [N1] -> [N2] -> [N3] -> [...] ->
 *                    ^-pos
 * [...] -> [M1] -> [M2] -> [...] -> [Mn] -> [Mn+1] -> [...] -> [NIL]
 *            ^-first                           ^-last
 *                    ||
 *                    \/
 * [...] -> [N1] -> [N2] -> [M2] -> [...] -> [Mn] -> [N3] -> [...] -> [NIL]
 *                    ^-pos 
 */
inline
void slist_transfer_after(slist_node_t *pos, 
	slist_node_t *first, slist_node_t *last)
{
	slist_node_t *keep = first;
	if (first == last || (first = first->next) == last)
		return;

	keep->next = last;
	if (pos->next != NULL || last != NULL) {
		last = slist_get_prev(first, last);
		last->next = pos->next;
	}
	pos->next = first;
}

/**
 * reverse singly linked list after pos
 * [...] -> [N1] -> [N2] -> [N3] -> [N4] -> [...] -> [NIL]
 *            ^-pos   ^-tail  ^-keep
 *                ||
 *                \/
 * [...] -> [N1] -> [N3] -> [N2] -> [N4] -> [...] -> [NIL]
 *            ^-pos           ^-tail  ^-keep
 *
 */
inline
void slist_reverse_after(slist_node_t *pos, slist_node_t *nil)
{
	if (pos == nil || pos->next == nil)
		return;

	slist_node_t *tail = pos->next;
	slist_node_t *keep = tail->next; 
	for ( ; keep != nil; keep = tail->next) {
		tail->next = keep->next;	// remove keep from list

		keep->next = pos->next;	// insert keep after node
		pos->next = keep;
	}
}

#ifdef __cplusplus
/**
 * search first equal key's node in [first, last)
 */
template <typename T, typename BinaryPredicate, typename UnaryFunction>
slist_node_t *slist_search(const slist_node_t *first, const slist_node_t *last,
	const T &key, BinaryPredicate equal, UnaryFunction get_key)
{
	while (first != last && !equal(get_key(first), key)) {
		first = first->next;
	}
	return (slist_node_t *) first;
}

/**
 * search first node in [first, last) which pred return true
 */
template <typename UnaryPredicate, typename UnaryFunction>
slist_node_t *slist_search(const slist_node_t *first, const slist_node_t *last,
	UnaryPredicate pred, UnaryFunction get_key)
{
	while (first != last && !pred(get_key(first))) {
		first = first->next;
	}
	return (slist_node_t *) first;
}

/**
 * search first equal key's node in (first, last),
 * and get prev node link
 */
template <typename T, typename BinaryPredicate, typename UnaryFunction>
slist_node_t *slist_search_after(
	const slist_node_t *first, const slist_node_t *last,
	const T &key, BinaryPredicate equal, UnaryFunction get_key,
	slist_node_t **prev)
{
	const slist_node_t *keep = first;
	first = first->next;
	while ((first != last) && !equal(get_key(first), key)) {
		keep = first;
		first = first->next;
	}
	*prev = (slist_node_t *) keep;

	return (slist_node_t *) first;
}

/**
 * search first node in (first, last) which pred return true
 * and get prev node link
 */
template <typename UnaryPredicate, typename UnaryFunction>
slist_node_t *slist_search_after(
	const slist_node_t *first, const slist_node_t *last,
	UnaryPredicate pred, UnaryFunction get_key,
	slist_node_t **prev)
{
	const slist_node_t *keep = first;
	first = first->next;
	while ((first != last) && !pred(get_key(first))) {
		keep = first;
		first = first->next;
	}
	*prev = (slist_node_t *) keep;

	return (slist_node_t *) first;
}

/**
 * op on range [fist, last)
 */
template <typename UnaryOperation>
void slist_foreach(slist_node_t *first, slist_node_t *last, UnaryOperation op)
{
	slist_node_t *keep;
	while (first != last) {
		keep = first->next;
		op(first);
		first = keep;
	}
}

/**
 * destroy list
 */
template <typename UnaryOperation>
void slist_destroy(slist_t *lst, UnaryOperation destroy)
{
	slist_foreach<UnaryOperation>(lst->head.next, NULL, destroy);
}

/**
 * merge src list (src_pos, src_nil) to dst list (dst_pos, dst_nil), 
 * assume both list range are sorted
 */
template <typename BinaryPredicate, typename UnaryFunction>
void slist_merge_after(slist_node_t *dst_pos, slist_node_t *dst_nil, 
	slist_node_t *src_pos, slist_node_t *src_nil, 
	BinaryPredicate less, UnaryFunction get_key)
{
	if (dst_pos == dst_nil || src_pos == src_nil)
		return;

	slist_node_t *dst_beg = dst_pos->next;
	slist_node_t *src_beg = src_pos->next;
	while (dst_beg != dst_nil && src_beg != src_nil) {
		// find first greater than src_beg in dst list, 
		// is the insert pos in dst list
		while (dst_beg != dst_nil && 
			!less(get_key(src_beg), get_key(dst_beg))) {
			dst_pos = dst_beg;
			dst_beg = dst_beg->next;
		}
		if (dst_beg == dst_nil) // nofound
			break;

		// find first pos greater than dst_beg in src list,
		// range [src_beg, src_end) is the transfer range
		slist_node_t *src_end = src_beg->next;
		while (src_end != src_nil && 
			!less(get_key(dst_beg), get_key(src_end))) {
			src_end = src_end->next;
		}

		// transfer [src_beg, src_pos) insert after dst_pos
		slist_transfer_after(dst_pos, src_pos, src_end);

		// because dst_beg's key < src_end's key, move dst_pos to dst_beg
		dst_pos = dst_beg;

		// update dst_beg and src_beg
		dst_beg = dst_pos->next;
		src_beg = src_pos->next;
	}
	
	if (dst_beg == dst_nil) {
		slist_transfer_after(dst_pos, src_pos, src_nil);
	}
}

/**
 * remove duplicate values in list
 */
template <typename BinaryPredicate, typename UnaryFunction,
	typename UnaryOperation>
void slist_unique(slist_node_t *first, slist_node_t *last,
	BinaryPredicate equal, UnaryFunction get_key, UnaryOperation destroy)
{
	while (first != last) {
		// find pos that not equal first's value
		slist_node_t *pos = first->next;
		while (pos != last && equal(get_key(pos), get_key(first)))
			pos = pos->next;
		slist_node_t *beg = first->next;
		slist_range_remove_after(first, pos);
		slist_foreach(beg, pos, destroy);
		first = pos;
	}
}
#endif // __cplusplus

#ifdef __cplusplus
} // namespace detail
} // namespace Hx
#endif // __cplusplus

#endif // HX_SLIST_IMPL_H

