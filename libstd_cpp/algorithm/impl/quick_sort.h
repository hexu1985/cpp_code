// -*- C++ -*-
// HeXu's
// 2014 Mar

#ifndef HX_QUICK_SORT_H
#define HX_QUICK_SORT_H

#include <iterator>

namespace Hx {

namespace algo_detail {

template <typename T, typename RandomAccessIterator>
RandomAccessIterator partition(RandomAccessIterator first, 
	RandomAccessIterator last)
{
	using std::swap;

	T key = *first;

	RandomAccessIterator i, j;
	i = first;
	j = last-1;

	// partition loop
	while (true) {
		// find first position that not greater than *first
		while (key < *j) {
			--j;
		}

		// find not less than *first
		while (*i < key) {
			++i;
		}

		if (i < j) {
			swap(*i, *j);
		} else {
			return j;
		}
	}
}

template <typename T, typename RandomAccessIterator, typename Compare>
RandomAccessIterator partition(RandomAccessIterator first, 
	RandomAccessIterator last, Compare less)
{
	using std::swap;

	T key = *first;

	RandomAccessIterator i, j;
	i = first;
	j = last-1;

	// partition loop
	while (true) {
		// find first position that not greater than *first
		while (less(key, *j)) {
			--j;
		}

		// find not less than *first
		while (less(*i, key)) {
			++i;
		}

		if (i < j) {
			swap(*i, *j);
		} else {
			return j;
		}
	}
}

template <typename T, typename RandomAccessIterator>
void quick_sort(RandomAccessIterator first, RandomAccessIterator last)
{
	if (first+1 < last) {
		RandomAccessIterator q = partition<T>(first, last);
		quick_sort<T>(first, q);
		quick_sort<T>(q+1, last);
	}
}

template <typename T, typename RandomAccessIterator, typename Compare>
void quick_sort(RandomAccessIterator first, RandomAccessIterator last,
	Compare less)
{
	if (first+1 < last) {
		RandomAccessIterator q = partition<T>(first, last, less);
		quick_sort<T>(first, q, less);
		quick_sort<T>(q+1, last, less);
	}
}

} // namespace algo_detail

/**
 * Sort elements in range
 * Sorts the elements in the range [first,last) into ascending order.
 */
template <class RandomAccessIterator>
void quick_sort(RandomAccessIterator first, RandomAccessIterator last)
{
	typedef typename std::iterator_traits<RandomAccessIterator>::value_type T;
	algo_detail::quick_sort<T>(first, last);
}

template <class RandomAccessIterator, class Compare>
void quick_sort(RandomAccessIterator first, RandomAccessIterator last, 
	Compare comp)
{
	typedef typename std::iterator_traits<RandomAccessIterator>::value_type T;
	algo_detail::quick_sort<T>(first, last, comp);
}

} // namespace Hx

#endif // HX_QUICK_SORT_H

