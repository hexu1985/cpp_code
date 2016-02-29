// -*- C++ -*-
// HeXu's
// 2014 Feb

#ifndef HX_HASH_STRING_H
#define HX_HASH_STRING_H

#include <string>
#include "key_words.h"

namespace Hx {

template <>
struct hash<std::string>: public hash_base<size_t, std::string> {
	size_t operator ()(const std::string &s) const noexcept
	{
		return hash_impl::hash(s.data(), s.length());
	}
};

template <>
struct hash<std::wstring>: public hash_base<size_t, std::wstring> {
	size_t operator ()(const std::wstring &s) const noexcept
	{
		return hash_impl::hash(s.data(), s.length() * sizeof(wchar_t));
	}
};

#if __cplusplus >= 201103L
template <>
struct hash<std::u16string>: public hash_base<size_t, std::u16string> {
	size_t operator ()(const std::u16string &s) const noexcept
	{
		return hash_impl::hash(s.data(), s.length() * sizeof(wchar_t));
	}
};

template <>
struct hash<std::u32string>: public hash_base<size_t, std::u32string> {
	size_t operator ()(const std::u32string &s) const noexcept
	{
		return hash_impl::hash(s.data(), s.length() * sizeof(wchar_t));
	}
};
#endif // __cplusplus >= 201103L

} // namespace Hx

#endif // HX_HASH_STRING_H

