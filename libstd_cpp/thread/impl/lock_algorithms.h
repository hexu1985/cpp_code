// -*- C++ -*-
// HeXu's
// 2013 May
// modify from boost/thread/lock_algorithms.hpp

// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// (C) Copyright 2007 Anthony Williams
// (C) Copyright 2011-2012 Vicente J. Botet Escriba

#ifndef HX_LOCK_ALGORITHMS_H
#define HX_LOCK_ALGORITHMS_H

#include <algorithm>
#include <iterator>
#include "unique_lock.h"

namespace Hx {

namespace detail {

template <typename M1, typename M2>
unsigned try_lock_internal(M1& m1, M2& m2)
{
	Hx::unique_lock<M1> l1(m1, Hx::try_to_lock);
	if (!l1) {
		return 1;
	}
	if (!m2.try_lock()) {
		return 2;
	}
	l1.release();
	return 0;
}

template <typename M1, typename M2, typename M3>
unsigned try_lock_internal(M1& m1, M2& m2, M3& m3)
{
	Hx::unique_lock<M1> l1(m1, Hx::try_to_lock);
	if (!l1) {
		return 1;
	}
	if (unsigned const failed_lock = try_lock_internal(m2, m3)) {
		return failed_lock + 1;
	}
	l1.release();
	return 0;
}

template <typename M1, typename M2, typename M3, typename M4>
unsigned try_lock_internal(M1& m1, M2& m2, M3& m3, M4& m4)
{
	Hx::unique_lock<M1> l1(m1, Hx::try_to_lock);
	if (!l1) {
		return 1;
	}
	if (unsigned const failed_lock = try_lock_internal(m2, m3, m4)) {
		return failed_lock + 1;
	}
	l1.release();
	return 0;
}

template <typename M1, typename M2, typename M3, typename M4, typename M5>
unsigned try_lock_internal(M1& m1, M2& m2, M3& m3, M4& m4, M5& m5)
{
	Hx::unique_lock<M1> l1(m1, Hx::try_to_lock);
	if (!l1) {
		return 1;
	}
	if (unsigned const failed_lock = try_lock_internal(m2, m3, m4, m5)) {
		return failed_lock + 1;
	}
	l1.release();
	return 0;
}

template <typename M1, typename M2>
unsigned lock_helper(M1& m1, M2& m2)
{
	Hx::unique_lock<M1> l1(m1);
	if (!m2.try_lock()) {
		return 1;
	}
	l1.release();
	return 0;
}

template <typename M1, typename M2, typename M3>
unsigned lock_helper(M1& m1, M2& m2, M3& m3)
{
	Hx::unique_lock<M1> l1(m1);
	if (unsigned const failed_lock = try_lock_internal(m2, m3)) {
		return failed_lock;
	}
	l1.release();
	return 0;
}

template <typename M1, typename M2, typename M3, typename M4>
unsigned lock_helper(M1& m1, M2& m2, M3& m3, M4& m4)
{
	Hx::unique_lock<M1> l1(m1);
	if (unsigned const failed_lock = try_lock_internal(m2, m3, m4)) {
		return failed_lock;
	}
	l1.release();
	return 0;
}

template <typename M1, typename M2, typename M3, typename M4, typename M5>
unsigned lock_helper(M1& m1, M2& m2, M3& m3, M4& m4, M5& m5)
{
	Hx::unique_lock<M1> l1(m1);
	if (unsigned const failed_lock = try_lock_internal(m2, m3, m4, m5)) {
		return failed_lock;
	}
	l1.release();
	return 0;
}

}	// namespace detail

template <typename M1, typename M2>
void lock(M1& m1, M2& m2)
{
	unsigned const lock_count = 2;
	unsigned lock_first = 0;
	for (;;) {
		switch (lock_first) {
		case 0:
			lock_first = Hx::detail::lock_helper(m1, m2);
			if (!lock_first) return;
			break;
		case 1:
			lock_first = Hx::detail::lock_helper(m2, m1);
			if (!lock_first) return;
			lock_first = (lock_first + 1) % lock_count;
			break;
		}
	}
}

template <typename M1, typename M2, typename M3>
void lock(M1& m1, M2& m2, M3& m3)
{
	unsigned const lock_count = 3;
	unsigned lock_first = 0;
    for (;;) {
		switch (lock_first) {
		case 0:
			lock_first = Hx::detail::lock_helper(m1, m2, m3);
			if (!lock_first) return;
			break;
		case 1:
			lock_first = Hx::detail::lock_helper(m2, m3, m1);
			if (!lock_first) return;
			lock_first = (lock_first + 1) % lock_count;
			break;
		case 2:
			lock_first = Hx::detail::lock_helper(m3, m1, m2);
			if (!lock_first) return;
			lock_first = (lock_first + 2) % lock_count;
			break;
		}
	}
}

template <typename M1, typename M2, typename M3, typename M4>
void lock(M1& m1, M2& m2, M3& m3, M4& m4)
{
	unsigned const lock_count = 4;
	unsigned lock_first = 0;
	for (;;) {
		switch (lock_first) {
		case 0:
			lock_first = Hx::detail::lock_helper(m1, m2, m3, m4);
			if (!lock_first) return;
			break;
		case 1:
			lock_first = Hx::detail::lock_helper(m2, m3, m4, m1);
			if (!lock_first) return;
			lock_first = (lock_first + 1) % lock_count;
			break;
		case 2:
			lock_first = Hx::detail::lock_helper(m3, m4, m1, m2);
			if (!lock_first) return;
			lock_first = (lock_first + 2) % lock_count;
			break;
		case 3:
			lock_first = Hx::detail::lock_helper(m4, m1, m2, m3);
			if (!lock_first) return;
			lock_first = (lock_first + 3) % lock_count;
			break;
		}
	}
}

template <typename M1, typename M2, typename M3, typename M4, typename M5>
void lock(M1& m1, M2& m2, M3& m3, M4& m4, M5& m5)
{
	unsigned const lock_count = 5;
	unsigned lock_first = 0;
	for (;;) {
		switch (lock_first) {
		case 0:
			lock_first = Hx::detail::lock_helper(m1, m2, m3, m4, m5);
			if (!lock_first) return;
			break;
		case 1:
			lock_first = Hx::detail::lock_helper(m2, m3, m4, m5, m1);
			if (!lock_first) return;
			lock_first = (lock_first + 1) % lock_count;
			break;
		case 2:
			lock_first = Hx::detail::lock_helper(m3, m4, m5, m1, m2);
			if (!lock_first) return;
			lock_first = (lock_first + 2) % lock_count;
			break;
		case 3:
			lock_first = Hx::detail::lock_helper(m4, m5, m1, m2, m3);
			if (!lock_first) return;
			lock_first = (lock_first + 3) % lock_count;
			break;
		case 4:
			lock_first = Hx::detail::lock_helper(m5, m1, m2, m3, m4);
			if (!lock_first) return;
			lock_first = (lock_first + 4) % lock_count;
			break;
		}
	}
}

template <typename M1, typename M2>
int try_lock(M1& m1, M2& m2)
{
	return ((int) Hx::detail::try_lock_internal(m1, m2)) - 1;
}

template <typename M1, typename M2, typename M3>
int try_lock(M1& m1, M2& m2, M3& m3)
{
	return ((int) Hx::detail::try_lock_internal(m1, m2, m3)) - 1;
}

template <typename M1, typename M2, typename M3, typename M4>
int try_lock(M1& m1, M2& m2, M3& m3, M4& m4)
{
	return ((int) Hx::detail::try_lock_internal(m1, m2, m3, m4)) - 1;
}

template <typename M1, typename M2, typename M3, typename M4, typename M5>
int try_lock(M1& m1, M2& m2, M3& m3, M4& m4, M5& m5)
{
	return ((int) Hx::detail::try_lock_internal(m1, m2, m3, m4, m5)) - 1;
}

}	// namespace Hx

#endif
