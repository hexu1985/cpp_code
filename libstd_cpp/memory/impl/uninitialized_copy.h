// -*- C++ -*-
// HeXu's
// 2013 Aug

#ifndef HX_UNINITIALIZED_COPY_H
#define HX_UNINITIALIZED_COPY_H

#include <iterator>

namespace Hx {

/**
 * Copy block of memory
 * Constructs copies of the elements in the range [first,last) 
 * into a range beginning at result and returns 
 * an iterator to the last element in the destination range.
 * Unlike algorithm copy, uninitialized_copy constructs the objects in-place, 
 * instead of just copying them. This allows to obtain fully constructed copies 
 * of the elements into a range of uninitialized memory, 
 * such as a memory block obtained by a call to get_temporary_buffer or malloc.
 */
template <typename InputIterator, typename ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last,
	ForwardIterator result)
{
	typedef typename 
		std::iterator_traits<ForwardIterator>::value_type value_type;
	ForwardIterator save(result);
	try
	{
		for (; first != last; ++result, ++first)
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

}	// namespace Hx

#endif // HX_UNINITIALIZED_COPY_H

