// -*- C++ -*-
// HeXu's
// 2013 Sep

#ifndef HX_COPY_N_H
#define HX_COPY_N_H

namespace Hx {

/**
 * Copy elements
 * Copies the first n elements from the range beginning at first 
 * into the range beginning at result.
 * The function returns an iterator to the end of the destination range 
 * (which points to one past the last element copied).
 * If n is negative, the function does nothing.
 * If the ranges overlap, some of the elements in the range pointed 
 * by result may have undefined but valid values.
 */
template <typename InputIterator, typename Size, typename OutputIterator>
inline
OutputIterator copy_n(InputIterator first, Size n, OutputIterator result)
{
	while (n > 0) {
		*result = *first;
		++result; ++first;
		--n;
	}
	return result;
}

} // namespace Hx

#if __cplusplus < 201103L
namespace std {

using Hx::copy_n;

}
#endif // __cplusplus < 201103L

#endif // HX_COPY_N_H

