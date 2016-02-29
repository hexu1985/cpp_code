// -*- C++ -*-
// HeXu's
// 2013 Jun

#ifndef HX_THREAD_ID_H
#define HX_THREAD_ID_H

#include <pthread.h>
#include <iosfwd>
#include "key_words.h"
#include "functional.h"

namespace Hx {

/**
 * The class thread_id is a lightweight, trivially copyable class 
 * that serves as a unique identifier of thread objects.
 */
struct thread_id {
	pthread_t id;	// native thread handle

	typedef	pthread_t native_handle_type;

	/**
	 * Default-constructs a new thread identifier. 
	 * The identifier does not represent a thread. 
	 */
	thread_id(): id(-1) {} 

	thread_id(pthread_t tid) { id = tid; }

	thread_id &operator =(pthread_t tid) { id = tid; return *this; }

	/** Compares two thread identifiers. */
	friend bool operator ==(const thread_id &lhs, const thread_id &rhs);
	friend bool operator !=(const thread_id &lhs, const thread_id &rhs);
	friend bool operator <(const thread_id &lhs, const thread_id &rhs);
	friend bool operator <=(const thread_id &lhs, const thread_id &rhs);
	friend bool operator >(const thread_id &lhs, const thread_id &rhs);
	friend bool operator >=(const thread_id &lhs, const thread_id &rhs);

	/** 
	 * Returns the underlying implementation-defined native handle object. 
	 */
	native_handle_type native_handle() const { return id; }

	/** Exchanges the underlying handles of two thread objects. */
	void swap(thread_id &other)
	{
		pthread_t tmp = id;
		id = other.id;
		other.id = tmp;
	}
};

inline bool operator ==(const thread_id &lhs, const thread_id &rhs)
{
	return pthread_equal(lhs.id, rhs.id);
}

inline bool operator !=(const thread_id &lhs, const thread_id &rhs)
{
	return !(lhs == rhs);
}

inline bool operator <(const thread_id &lhs, const thread_id &rhs)
{
	return lhs.id < rhs.id;
}

inline bool operator <=(const thread_id &lhs, const thread_id &rhs)
{
	return !(rhs < lhs);
}

inline bool operator >(const thread_id &lhs, const thread_id &rhs)
{
	return (rhs < lhs);
}

inline bool operator >=(const thread_id &lhs, const thread_id &rhs)
{
	return !(lhs < rhs);
}

// reload operator <<, print function
template <typename charT, typename traits>
std::basic_ostream<charT, traits> &operator <<(
	std::basic_ostream<charT, traits> &os, const thread_id &id)
{
	os << id.native_handle();
	return os;
}

}	// namespace Hx

#if __cplusplus >= 201103L
namespace std {
#else
namespace std {
namespace tr1 {
#endif

template <> struct hash<Hx::thread_id>
{
	size_t operator ()(const Hx::thread_id &id) const noexcept
	{
		return static_cast<size_t>(id.native_handle());
	}
};

#if __cplusplus >= 201103L
}	// namespace std
#else
}	// namespace tr1
}	// namespace std
#endif

#endif

