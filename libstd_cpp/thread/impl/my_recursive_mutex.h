// -*- C++ -*-
// HeXu's
// 2013 Jun

#ifndef HX_RECURSIVE_MUTEX_H
#define HX_RECURSIVE_MUTEX_H

#include <cassert>
#include "condition_variable.h"
#include "mutex.h"
#include "unique_lock.h"
#include "thread_id.h"
#include "this_thread.h"

namespace Hx {

/**
 * The recursive_mutex class is a synchronization primitive 
 * that can be used to protect shared data from being simultaneously 
 * accessed by multiple threads. 
 * recursive_mutex offers exclusive, recursive ownership semantics.
 */
class recursive_mutex {
private:
	mutex mtx_;	// basic lock on this recursive_mutex
	condition_variable cnd_;	// for threads waiting
	thread_id owner_tid_;	// the lock owner's thread id
	int locked_depth_;	// the depth of this recursive_mutex

public:
	/** 
	 * Constructs the mutex. The mutex is in unlocked state after the call. 
	 */
	recursive_mutex(): owner_tid_(), locked_depth_() {}

#if __cplusplus >= 201103L
	recursive_mutex(const recursive_mutex &) = delete;
	recursive_mutex &operator =(const recursive_mutex &) = delete;
#else
private:
	recursive_mutex(const recursive_mutex &);
	recursive_mutex &operator =(const recursive_mutex &);
public:
#endif

	/**
	 * Locks the mutex. If another thread has already locked the mutex, 
	 * a call to lock will block execution until the lock is acquired. 
	 * A thread may call lock on a recursive mutex repeatedly. 
	 * Ownership will only be released after the thread 
	 * makes a matching number of calls to unlock. 
	 */
	void lock()
	{
		unique_lock<mutex> lock(mtx_);
		thread_id current_tid = this_thread::get_id();
		while (locked_depth_ != 0 && current_tid != owner_tid_) {
			cnd_.wait(lock);
		}

		if (locked_depth_ == 0) {
			locked_depth_++;
			owner_tid_ = current_tid;
		} else {	// owner_tid_ == current_tid
			locked_depth_++;
		}
	}

	/**
	 * Tries to lock the mutex. Returns immediately. 
	 * On successful lock acquisition returns true, otherwise returns false.
	 * The behavior is undefined if the mutex is not unlocked 
	 * before being destroyed, i.e. some thread still owns it. 
	 */
	bool try_lock()
	{
		unique_lock<mutex> lock(mtx_);
		thread_id current_tid = this_thread::get_id();
		if (locked_depth_ == 0) {	// no one hold the lock
			locked_depth_++;
			owner_tid_ = current_tid;
			return true;
		} else if (current_tid == owner_tid_) {
			locked_depth_++;
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Unlocks the mutex.
	 * The mutex must be unlocked by all threads 
	 * that have successfully locked it before being destroyed. 
	 * Otherwise, the behavior is undefined. 
	 */
	void unlock()
	{
		unique_lock<mutex> lock(mtx_);
		assert(this_thread::get_id() == owner_tid_);
		if (--locked_depth_ == 0) {	// decrease locked depth
			owner_tid_ = thread_id();
			cnd_.notify_all();
		}
	}
};

}	// namespace Hx

#endif

