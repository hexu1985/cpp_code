// -*- C++ -*-
// HeXu's
// 2013 Jul

#ifndef HX_NUMERIC_LIMITS_H
#define HX_NUMERIC_LIMITS_H

#include <cfloat>
#include <limits>
#include "key_words.h"

namespace Hx {

template <typename T>
struct numeric_limits: public std::numeric_limits<T> {
	static constexpr T lowest() noexcept { return T(); }
};

template <>
struct numeric_limits<bool>: public std::numeric_limits<bool> {
	static constexpr bool lowest() noexcept { return min(); }
};

template <>
struct numeric_limits<char>: public std::numeric_limits<char> {
	static constexpr char lowest() noexcept { return min(); }
};

template <>
struct numeric_limits<signed char>: public std::numeric_limits<signed char> {
	static constexpr signed char lowest() noexcept { return min(); }
};

template <>
struct numeric_limits<unsigned char>: public std::numeric_limits<unsigned char> {
	static constexpr unsigned char lowest() noexcept { return min(); }
};

template <>
struct numeric_limits<wchar_t>: public std::numeric_limits<wchar_t> {
	static constexpr wchar_t lowest() noexcept { return min(); }
};

template <>
struct numeric_limits<short>: public std::numeric_limits<short> {
	static constexpr short lowest() noexcept { return min(); }
};

template <>
struct numeric_limits<unsigned short>: public std::numeric_limits<unsigned short> {
	static constexpr unsigned short lowest() noexcept { return min(); }
};

template <>
struct numeric_limits<int>: public std::numeric_limits<int> {
	static constexpr int lowest() noexcept { return min(); }
};

template <>
struct numeric_limits<unsigned int>: public std::numeric_limits<unsigned int> {
	static constexpr unsigned int lowest() noexcept { return min(); }
};

template <>
struct numeric_limits<long>: public std::numeric_limits<long> {
	static constexpr long lowest() noexcept { return min(); }
};

template <>
struct numeric_limits<unsigned long>: public std::numeric_limits<unsigned long> {
	static constexpr unsigned long lowest() noexcept { return min(); }
};

template <>
struct numeric_limits<long long>: public std::numeric_limits<long long> {
	static constexpr long long lowest() noexcept { return min(); }
};

template <>
struct numeric_limits<unsigned long long>: public std::numeric_limits<unsigned long long> {
	static constexpr unsigned long long lowest() noexcept { return min(); }
};

template <>
struct numeric_limits<float>: public std::numeric_limits<float> {
	static constexpr float lowest() noexcept { return -FLT_MAX; }
};

template <>
struct numeric_limits<double>: public std::numeric_limits<double> {
	static constexpr double lowest() noexcept { return -DBL_MAX; }
};

template <>
struct numeric_limits<long double>: public std::numeric_limits<long double> {
	static constexpr long double lowest() noexcept { return -LDBL_MAX; }
};

} // namespace Hx

#endif // HX_NUMERIC_LIMITS_H

