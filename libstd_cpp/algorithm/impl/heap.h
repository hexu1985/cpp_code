// -*- C++ -*-
// HeXu's
// 2014 Mar

#ifndef HX_HEAP_H
#define HX_HEAP_H

namespace Hx {

/** 
 * MAX BINARY HEAP:
 *
 *                16(1)
 *               /   \ 
 *             /       \ 
 *           /           \ 
 *         14(2)          10(3)
 *        /  \           /  \ 
 *      /      \       /      \ 
 *     8(4)     7(5)  9(6)    3(7)
 *   /   \     /  \
 *  2(8) 4(9) 1(10) 
 *
 *  | 1| 2| 3| 4| 5| 6| 7| 8| 9|10|
 *  |16|14|10| 8| 7| 9| 3| 2| 4| 1|
 */

inline ptrdiff_t heap_parent(ptrdiff_t i) { return i/2; }
inline ptrdiff_t heap_left(ptrdiff_t i) { return 2*i; }
inline ptrdiff_t heap_right(ptrdiff_t i) { return 2*i+1; }

template <typename RandomAccessIterator>
inline RandomAccessIterator heap_parent(RandomAccessIterator first, 
	RandomAccessIterator pos)
{
	return (first-1)+heap_parent(pos-(first-1));
}

template <typename RandomAccessIterator>
inline RandomAccessIterator heap_left(RandomAccessIterator first, 
	RandomAccessIterator pos)
{
	return (first-1)+heap_left(pos-(first-1));
}

template <typename RandomAccessIterator>
inline RandomAccessIterator heap_right(RandomAccessIterator first, 
	RandomAccessIterator pos)
{
	return (first-1)+heap_right(pos-(first-1));
}

/**
 * In order to maintain the max-heap property, When it is called, 
 * heapify assumes that the binary trees rooted at heap_left(pos) 
 * and heap_right(pos) are maxheaps, but that *pos might be smaller than 
 * its children, thus violating the max-heap property.
 */
template <typename RandomAccessIterator>
void max_heapify(RandomAccessIterator first, RandomAccessIterator last, 
	RandomAccessIterator pos)
{
	using std::swap;

	RandomAccessIterator l, r, largest;
	l = heap_left(first, pos);
	r = heap_right(first, pos);

	// compare left child with pos, tag largest
	if (l < last && *pos < *l) {
		largest = l;
	} else {
		largest = pos;
	}

	// compare largest with right child
	if (r < last && *largest < *r) {
		largest = r;
	}

	if (largest != pos) {
		swap(*pos, *largest);
		max_heapify(first, last, largest);
	}
}

template <typename RandomAccessIterator, typename Compare>
void max_heapify(RandomAccessIterator first, RandomAccessIterator last, 
	RandomAccessIterator pos, Compare less)
{
	using std::swap;

	RandomAccessIterator l, r, largest;
	l = heap_left(first, pos);
	r = heap_right(first, pos);

	// compare left child with pos, tag largest
	if (l < last && less(*pos, *l)) {
		largest = l;
	} else {
		largest = pos;
	}

	// compare largest with right child
	if (r < last && less(*largest, *r)) {
		largest = r;
	}

	if (largest != pos) {
		swap(*pos, *largest);
		max_heapify(first, last, largest);
	}
}

/**
 * Make heap from range
 * Rearranges the elements in the range [first,last) in such a way 
 * that they form a heap.
 */
template <typename RandomAccessIterator>
void make_heap(RandomAccessIterator first, RandomAccessIterator last)
{
	// find last pos's parent
	RandomAccessIterator pos = heap_parent(first, last-1);	
	while (pos >= first) {
		max_heapify(first, last, pos);
		--pos;
	}
}

template <typename RandomAccessIterator, typename Compare>
void make_heap(RandomAccessIterator first, RandomAccessIterator last,
	Compare less)
{
	// find last pos's parent
	RandomAccessIterator pos = heap_parent(first, last-1);	
	while (pos >= first) {
		max_heapify(first, last, pos, less);
		--pos;
	}
}

/**
 * Sort elements of heap
 * Sorts the elements in the heap range [first,last) into ascending order.
 */
template <typename RandomAccessIterator>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
{
	using std::swap;

	for (RandomAccessIterator pos = last-1; pos > first; --pos) {
		swap(*first, *pos);
		max_heapify(first, pos, first);
	}
}

template <typename RandomAccessIterator, typename Compare>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last,
	Compare less)
{
	using std::swap;

	for (RandomAccessIterator pos = last-1; pos > first; --pos) {
		swap(*first, *pos);
		max_heapify(first, pos, first, less);
	}
}

/**
 * Sort elements in range
 * Sorts the elements in the range [first,last) into ascending order.
 */
template <typename RandomAccessIterator>
void heap_sort(RandomAccessIterator first, RandomAccessIterator last)
{
	make_heap(first, last);
	sort_heap(first, last);
}

template <typename RandomAccessIterator, typename Compare>
void heap_sort(RandomAccessIterator first, RandomAccessIterator last,
	Compare less)
{
	make_heap(first, last, less);
	sort_heap(first, last, less);
}

/**
 * Push element into heap range
 * Given a heap in the range [first,last-1), this function extends the range 
 * considered a heap to [first,last) by placing the value in (last-1) 
 * into its corresponding location within it.
 */
template <typename RandomAccessIterator>
void push_heap(RandomAccessIterator first, RandomAccessIterator last)
{
	using std::swap;

	RandomAccessIterator pos = last-1;
	RandomAccessIterator keep = heap_parent(first, pos); // keep pos's parent
	while (pos > first && *keep < *pos) {
		swap(*keep, *pos);
		pos = keep;
		keep = heap_parent(first, keep);
	}
}

template <typename RandomAccessIterator, typename Compare>
void push_heap(RandomAccessIterator first, RandomAccessIterator last,
	Compare less)
{
	using std::swap;

	RandomAccessIterator pos = last-1;
	RandomAccessIterator keep = heap_parent(first, pos); // keep pos's parent
	while (pos > first && less(*keep, *pos)) {
		swap(*keep, *pos);
		pos = keep;
		keep = heap_parent(first, keep);
	}
}

/**
 * Pop element from heap range
 * Rearranges the elements in the heap range [first,last) in such a way 
 * that the part considered a heap is shortened by one: The element with 
 * the highest value is moved to (last-1).
 */
template <typename RandomAccessIterator>
void pop_heap(RandomAccessIterator first, RandomAccessIterator last)
{
	using std::swap;

	if (first < --last) {
		swap(*first, *last);
		max_heapify(first, last, first);
	}
} 

template <typename RandomAccessIterator, typename Compare>
void pop_heap(RandomAccessIterator first, RandomAccessIterator last,
	Compare less)
{
	using std::swap;

	if (first < --last) {
		swap(*first, *last);
		max_heapify(first, last, first, less);
	}
} 

} // namespace Hx

#endif // HX_HEAP_H

