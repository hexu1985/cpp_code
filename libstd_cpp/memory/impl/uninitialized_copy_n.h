// -*- C++ -*-
// HeXu's
// 2013 Aug

#ifndef HX_UNINITIALIZED_COPY_N_H
#define HX_UNINITIALIZED_COPY_N_H

#include <iterator>

namespace Hx {

/**
 * Copy block of memory
 * Constructs copies of the n first elements of the array pointed by 
 * first into a range beginning at result and returns an iterator 
 * to the last element in the destination range.
 * Unlike algorithm copy_n, uninitialized_copy_n constructs the objects 
 * in-place, instead of just copying them. This allows to obtain fully 
 * constructed copies of the elements into a range of uninitialized memory, 
 * such as a memory block obtained by a call to get_temporary_buffer or malloc.
 */
template <typename InputIterator, typename Size, typename ForwardIterator>
ForwardIterator uninitialized_copy_n(InputIterator first, Size n,
	ForwardIterator result)
{
	typedef typename 
		std::iterator_traits<ForwardIterator>::value_type value_type;
	ForwardIterator save(result);
	try
	{
		for (; n > 0; ++result, ++first, --n)
			new (static_cast<void *>(&*result)) value_type(*first);
	}
	catch (...)
	{
		for (; save != result; ++save)
			save->~value_type();
		throw;
	}
	return result;
}

} // namespace Hx

#endif // HX_UNINITIALIZED_COPY_N_H

