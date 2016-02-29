// -*- C++ -*-
// HeXu's
// 2014 Mar

#ifndef HX_SORT_H
#define HX_SORT_H

#include <cstddef>
#include <iterator>
#include "insertion_sort.h"
#include "quick_sort.h"

namespace Hx {

namespace algo_detail {

const ptrdiff_t SORT_SIZE_THRESHOLD = 4;

template <typename T, typename RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last)
{
	if (last-first < SORT_SIZE_THRESHOLD) {
		insertion_sort<T>(first, last);
	} else {
		RandomAccessIterator q = partition<T>(first, last);
		sort<T>(first, q);
		sort<T>(q+1, last);
	}
}

template <typename T, typename RandomAccessIterator, typename Compare>
void sort(RandomAccessIterator first, RandomAccessIterator last,
	Compare less)
{
	if (last-first < SORT_SIZE_THRESHOLD) {
		insertion_sort<T>(first, last, less);
	} else {
		RandomAccessIterator q = partition<T>(first, last, less);
		sort<T>(first, q, less);
		sort<T>(q+1, last, less);
	}
}

} // namespace algo_detail

/**
 * Sort elements in range
 * Sorts the elements in the range [first,last) into ascending order.
 */
template <class RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last)
{
	typedef typename std::iterator_traits<RandomAccessIterator>::value_type T;
	algo_detail::sort<T>(first, last);
}

template <class RandomAccessIterator, class Compare>
void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	typedef typename std::iterator_traits<RandomAccessIterator>::value_type T;
	algo_detail::sort<T>(first, last, comp);
}

} // namespace Hx

#endif // HX_SORT_H

