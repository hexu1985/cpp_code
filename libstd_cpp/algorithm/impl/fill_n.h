// -*- C++ -*-
// HeXu's
// 2014 Apr

#ifndef HX_FILL_N_H
#define HX_FILL_N_H

namespace Hx {

/**
 * Fill sequence with value
 * Assigns val to the first n elements of the sequence pointed by first.
 */
template <typename OutputIterator, typename Size, typename T>
inline
OutputIterator fill_n(OutputIterator first, Size n, const T &val)
{
	while (n > 0) {
		*first = val;
		++first; --n;
	}
	return first;
}

} // namespace Hx

#endif // HX_FILL_N_H


