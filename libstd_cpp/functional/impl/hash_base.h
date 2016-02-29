// -*- C++ -*-
// HeXu's
// 2014 Feb

#ifndef HX_HASH_BASE_H
#define HX_HASH_BASE_H

#include <stddef.h>
#include "key_words.h"

namespace Hx {

template<typename Result, typename Arg>
struct hash_base {
	typedef Result result_type;
	typedef Arg argument_type;
};

// Primary class template hash.
template<typename T>
struct hash;

// Partial specializations for pointer types.
template<typename T>
struct hash<T *>: public hash_base<size_t, T *> {
	size_t operator ()(T *p) const noexcept
	{
		return reinterpret_cast<size_t>(p); 
	}
};

// Explicit specializations for integer types.
#define hashtable_define_trivial_hash(T) \
template<> \
struct hash<T> : public hash_base<size_t, T> { \
	size_t operator ()(T val) const noexcept \
	{ \
		return static_cast<size_t>(val); \
	} \
};

// Explicit specialization for bool.
hashtable_define_trivial_hash(bool)

// Explicit specialization for char.
hashtable_define_trivial_hash(char)

// Explicit specialization for signed char.
hashtable_define_trivial_hash(signed char)

// Explicit specialization for unsigned char.
hashtable_define_trivial_hash(unsigned char)

// Explicit specialization for wchar_t.
hashtable_define_trivial_hash(wchar_t)

#if __cplusplus >= 201103L
// Explicit specialization for char16_t.
hashtable_define_trivial_hash(char16_t)

// Explicit specialization for char32_t.
hashtable_define_trivial_hash(char32_t)
#endif // __cplusplus >= 201103L

// Explicit specialization for short.
hashtable_define_trivial_hash(short)

// Explicit specialization for int.
hashtable_define_trivial_hash(int)

// Explicit specialization for long.
hashtable_define_trivial_hash(long)

#if __cplusplus >= 201103L
// Explicit specialization for long long.
hashtable_define_trivial_hash(long long)
#endif // __cplusplus >= 201103L

// Explicit specialization for unsigned short.
hashtable_define_trivial_hash(unsigned short)

// Explicit specialization for unsigned int.
hashtable_define_trivial_hash(unsigned int)

// Explicit specialization for unsigned long.
hashtable_define_trivial_hash(unsigned long)

#if __cplusplus >= 201103L
// Explicit specialization for unsigned long long.
hashtable_define_trivial_hash(unsigned long long)
#endif // __cplusplus >= 201103L

#undef hashtable_define_trivial_hash

struct hash_impl {
	static size_t hash(const void *ptr, size_t len, 
		size_t seed = static_cast<size_t>(0xc70f6907UL))
	{
		const char *first = static_cast<const char *>(ptr);
		const char *last = first+len;
		for ( ; first != last; ++first) {
			seed ^= (size_t) *first + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}

	template<typename T>
	static size_t hash(const T &val)
	{
		return hash(&val, sizeof(val));
	}

	template<typename T>
	static size_t hash_combine(const T &val, size_t seed) 
	{
		return hash(&val, sizeof(val), seed); 
	}
};

// Specialization for float.
template<>
struct hash<float>: public hash_base<size_t, float> {
	size_t operator ()(float val) const noexcept
	{
		// 0 and -0 both hash to zero.
		return val != 0.0f ? hash_impl::hash(val) : 0;
	}
};

// Specialization for double.
template<>
struct hash<double>: public hash_base<size_t, double> {
	size_t operator ()(double val) const noexcept
	{
		// 0 and -0 both hash to zero.
		return val != 0.0 ? hash_impl::hash(val) : 0;
	}
};

#if __cplusplus >= 201103L
// Specialization for long double.
template<>
struct hash<long double>: public hash_base<size_t, long double> {
	size_t operator ()(long double val) const noexcept
	{
		// 0 and -0 both hash to zero.
		return val != 0.0 ? hash_impl::hash(val) : 0;
	}
};
#endif // __cplusplus >= 201103L
 
} // namespace Hx

#endif // HX_HASH_BASE_H
