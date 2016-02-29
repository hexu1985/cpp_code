// -*- C++ -*-
// HeXu's
// 2013 Aug

#ifndef HX_UNINITIALIZED_FILL_H
#define HX_UNINITIALIZED_FILL_H

#include <iterator>

namespace Hx {

/**
 * Fill block of memory
 * Constructs all the elements in the range [first,last) initializing them 
 * to a value of x.
 * Unlike algorithm fill, uninitialized_fill constructs the objects in-place, 
 * instead of just copying the value to them. This allows to obtain 
 * fully constructed copies into a range of uninitialized memory, 
 * such as a memory block obtained by a call to get_temporary_buffer or malloc.
 */
template <typename ForwardIterator, typename T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T &x)
{
	typedef typename 
		std::iterator_traits<ForwardIterator>::value_type value_type;
	ForwardIterator save(first);
	try
	{
		for (; first != last; ++first)
			new (static_cast<void *>(&*first)) value_type(x);
	}
	catch (...)
	{
		for (; save != first; ++save)
			save->~value_type();
		throw;
	}
}

}	// namespace Hx

#endif // HX_UNINITIALIZED_FILL_H

