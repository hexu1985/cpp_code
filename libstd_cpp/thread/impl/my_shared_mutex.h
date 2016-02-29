// -*- C++ -*-
// HeXu's
// 2013 Jun

#ifndef HX_SHARED_MUTEX_H
#define HX_SHARED_MUTEX_H

#include "mutex.h"
#include "unique_lock.h"
#include "condition_variable.h"

namespace Hx {

/**
 * The shared_mutex class is a synchronization primitive that can 
 * be used to protect shared data from being simultaneously 
 * accessed by multiple threads. 
 * Differently from other mutex types, there are two levels of access:
 * shared - several threads can share ownership of the same mutex. 
 * exclusive - only one thread can own the mutex. 
 * Shared mutexes are usually used in situations, when multiple readers 
 * can access the same resource at the same time without causing data races, 
 * but only one writer can do so. 
 */
class shared_mutex {
public:
	/**
	 * Constructs the mutex. 
	 * The mutex is in unlocked state after the call. 
	 */
	shared_mutex(): rd_wait_n_(0), wr_wait_n_(0), ref_count_(0) {}

#if __cplusplus >= 201103L
	shared_mutex(const shared_mutex &) = delete;
	shared_mutex &operator =(const shared_mutex &) = delete;
#else
private:
	shared_mutex(const shared_mutex &);
	shared_mutex &operator =(const shared_mutex &);
public:
#endif

	/** 
	 * locks the mutex, blocks if the mutex is not available 
	 */
	void lock()
	{
		unique_lock<mutex> lck(mtx_);
		while (ref_count_ != 0) {
			// ++wr_wait_n_ now, and --wr_wait_n_ when exit scoped 
			scoped_increment nwriterwaits(wr_wait_n_);
			wr_cnd_.wait(lck);
		}
		ref_count_ = -1;
	}

	/**
	 * tries to lock the mutex, returns if the mutex is not available
	 */
	bool try_lock()
	{
		unique_lock<mutex> lck(mtx_);
		if (ref_count_ != 0)
			return false;	// held by either writer or reader(s)
		else
			ref_count_ = -1;	// available, indicate a writer has it
		return true;
	}

	/**
	 * unlocks the mutex 
	 */
	void unlock()
	{
		unique_lock<mutex> lck(mtx_);
		if (ref_count_ > 0)
			ref_count_--;		// release a reader
		else if (ref_count_ == -1)
			ref_count_ = 0;	// release a writer

		// give preference to waiting writers over waiting readers
		if (wr_wait_n_ > 0) {
			if (ref_count_ == 0)
				wr_cnd_.notify_one();
		} else if (rd_wait_n_ > 0)
			rd_cnd_.notify_all();
	}

	/**
	 * locks the mutex for shared ownership, 
	 * blocks if the mutex is not available 
	 */
	void lock_shared()
	{
		unique_lock<mutex> lck(mtx_);
		// give preference to waiting writers
		while (ref_count_ < 0 || wr_wait_n_ > 0) {
			// ++rd_wait_n_ now, and --rd_wait_n_ when exit scoped
			scoped_increment nwraitreaders(rd_wait_n_);
			rd_cnd_.wait(lck);
		}
		ref_count_++;	// another reader has a read lock
	}

	/**
	 * tries to lock the mutex for shared ownership, 
	 * returns if the mutex is not available 
	 */
	bool try_lock_shared()
	{
		unique_lock<mutex> lck(mtx_);
		if (ref_count_ < 0 || wr_wait_n_ > 0)
			return false;	// held by a writer or waiting writers
		else
			ref_count_++;	// increment count of reader locks
		return true;
	}

	/** unlocks the mutex (shared ownership) */
	void unlock_shared() { unlock(); }

private:
	mutex mtx_;	// basic lock on this shared_mutex
	condition_variable rd_cnd_;	// for reader threads waiting
	condition_variable wr_cnd_;	// for writer threads waiting
	int rd_wait_n_;	// the number waiting of reader threads
	int wr_wait_n_;	// the number waiting of writer threads
	int ref_count_; // -1 if writer has the lock, else # readers holding the lock

private:
	class scoped_increment {
	private:
		int &ref;

	public:
		scoped_increment(int &val): ref(val)
		{
			++ref;
		}

		~scoped_increment() { --ref; }
	};
};

}	// namespace Hx

#endif
