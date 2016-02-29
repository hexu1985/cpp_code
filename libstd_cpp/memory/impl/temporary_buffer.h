// -*- C++ -*-
// HeXu's
// 2013 Aug

#ifndef HX_TEMPORARY_BUFFER_H
#define HX_TEMPORARY_BUFFER_H

#include <stddef.h>
#include <stdlib.h>
#include <utility>

namespace Hx {

/**
 * Get block of temporary memory
 * Requests a temporary block of storage to contain up to 
 * n elements of type T temporarily.
 * The block of storage is aligned apropriately to contain elements of type T 
 * if T has a fundamental alignment, although it is left uninitialized 
 * (no object is constructed).
 * This function is specifically designed to obtain memory of temporary nature 
 * (such as for the operations of an algorithm). Once the memory block is not 
 * needed anymore, it shall be released by calling return_temporary_buffer.
 * Notice that the actual size of the buffer returned may be smaller 
 * than requested (the actual size is indicated as part of the return value).
 */
template <typename T>
std::pair<T *, ptrdiff_t> get_temporary_buffer(ptrdiff_t n) throw()
{
	T *buffer = static_cast<T *>(calloc(sizeof (T), n));
	if (buffer == NULL)
		return std::make_pair((T *)NULL, ptrdiff_t(0));
	else
		return std::make_pair(buffer, n); 
}

/**
 * Return block of temporary memory
 * Releases the memory block pointed by p.
 * p shall be a pointer value returned by 
 * a previous call to get_temporary_buffer.
 */
template <typename T>
inline
void return_temporary_buffer(T *p) throw()
{
	free(p);
}

}	// namespace Hx

#endif // HX_TEMPORARY_BUFFER_H

