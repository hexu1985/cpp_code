// -*- C++ -*-
// HeXu's
// 2014 Mar

#ifndef HX_INSERTION_SORT_H
#define HX_INSERTION_SORT_H

#if __cplusplus >= 201103L
#include <functional>
#include <utility>
#endif // __cplusplus >= 201103L

#include <iterator>

namespace Hx {

namespace algo_detail {

#if __cplusplus >= 201103L
template <typename T, typename RandomAccessIterator, 
	typename Compare = std::less<T>>
void insertion_sort(RandomAccessIterator first, RandomAccessIterator last,
	Compare less = Compare())
{
	T key;
	for (RandomAccessIterator j = first+1; j < last; ++j) {
		key = std::move(*j);
		RandomAccessIterator i = j-1;
		while (i >= first && less(key, *i)) {
			*(i+1) = std::move(*i);
			--i;
		}
		*(i+1) = std::move(key);
	}
}
#else // !( __cplusplus >= 201103L )
template <typename T, typename RandomAccessIterator>
void insertion_sort(RandomAccessIterator first, RandomAccessIterator last)
{
	T key;
	for (RandomAccessIterator j = first+1; j < last; ++j) {
		key = *j;
		RandomAccessIterator i = j-1;
		while (i >= first && key < *i) {
			*(i+1) = *i;
			--i;
		}
		*(i+1) = key;
	}
}

template <typename T, typename RandomAccessIterator, typename Compare>
void insertion_sort(RandomAccessIterator first, RandomAccessIterator last,
	Compare less)
{
	T key;
	for (RandomAccessIterator j = first+1; j < last; ++j) {
		key = *j;
		RandomAccessIterator i = j-1;
		while (i >= first && less(key, *i)) {
			*(i+1) = *i;
			--i;
		}
		*(i+1) = key;
	}
}
#endif // __cplusplus >= 201103L

} // namespace algo_detail

/**
 * Sort elements in range
 * Sorts the elements in the range [first,last) into ascending order.
 */
template <class RandomAccessIterator>
void insertion_sort(RandomAccessIterator first, RandomAccessIterator last)
{
	typedef typename std::iterator_traits<RandomAccessIterator>::value_type T;
	algo_detail::insertion_sort<T>(first, last);
}

template <class RandomAccessIterator, class Compare>
void insertion_sort(RandomAccessIterator first, RandomAccessIterator last, 
	Compare comp)
{
	typedef typename std::iterator_traits<RandomAccessIterator>::value_type T;
	algo_detail::insertion_sort<T>(first, last, comp);
}

} // namespace Hx

#endif // HX_INSERTION_SORT_H

