// -*- C++ -*-
// HeXu's
// 2013 Aug

#ifndef HX_UNINITIALIZED_FILL_N_H
#define HX_UNINITIALIZED_FILL_N_H

#include <iterator>

namespace Hx {

/**
 * Fill block of memory
 * Constructs n elements in the array pointed by first, 
 * initializing them to a value of x.
 * Unlike algorithm fill_n, uninitialized_fill_n constructs the objects 
 * in-place, instead of just copying the value to them. This allows 
 * to obtain fully constructed copies into a range of uninitialized memory, 
 * such as a memory block obtained by a call to get_temporary_buffer or malloc.
 */
template <typename ForwardIterator, typename Size, typename T>
ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T &x)
{
	typedef typename 
		std::iterator_traits<ForwardIterator>::value_type value_type;
	ForwardIterator save(first);
	try
	{
		for (; n > 0; ++first, --n)
			new (static_cast<void *>(&*first)) value_type(x);
	}
	catch (...)
	{
		for (; save != first; ++save)
			save->~value_type();
		throw;
	}
	return first;
}

}	// namespace Hx

#endif // HX_UNINITIALIZED_FILL_N_H

