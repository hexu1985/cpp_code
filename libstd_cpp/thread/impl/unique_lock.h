// -*- C++ -*-
// HeXu's
// 2013 May

#ifndef HX_UNIQUE_LOCK_H
#define HX_UNIQUE_LOCK_H

#include <cassert>
#include <utility>

#include "chrono.h"
#include "lock_options.h"

namespace Hx {

/**
 * The class unique_lock is a general-purpose mutex ownership wrapper 
 * allowing deferred locking, timed locking, recursive locking, 
 * transfer of lock ownership, and use with condition variables. 
 * The unique_lock class is movable, but not copyable -- it meets 
 * the requirements of MoveConstructible and MoveAssignable but 
 * not of CopyConstructible or CopyAssignable. 
 */
template <typename Mutex>
class unique_lock {
	Mutex *mtx_;
	bool owns_lock_;

public:
	typedef Mutex mutex_type;

	/**
	 * Constructs a unique_lock with no associated mutex. 
	 */
	unique_lock() noexcept: mtx_(NULL), owns_lock_(false) {}

	/**
	 * Constructs a unique_lock with m as the associated mutex. 
	 * Additionally: Locks the associated mutex by calling m.lock(). 
	 */
	explicit unique_lock(mutex_type &m): mtx_(&m), owns_lock_(false)
	{
		mtx_->lock();
		owns_lock_ = true;
	}

	/**
	 * Constructs a unique_lock with m as the associated mutex. 
	 * Additionally: Does not lock the associated mutex. 
	 */
	unique_lock(mutex_type &m, defer_lock_t t) noexcept: 
		mtx_(&m), owns_lock_(false) {}

	/**
	 * Constructs a unique_lock with m as the associated mutex. 
	 * Additionally: ries to lock the associated mutex without blocking 
	 * by calling m.try_lock(). 
	 */
	unique_lock(mutex_type &m, try_to_lock_t t): mtx_(&m), owns_lock_(false)
	{
		owns_lock_ = mtx_->try_lock();
	}

	/**
	 * Constructs a unique_lock with m as the associated mutex. 
	 * Additionally: Assumes the calling thread already owns m. 
	 */
	unique_lock(mutex_type &m, adopt_lock_t t): mtx_(&m), owns_lock_(true) {}

#if __cplusplus >= 201103L
	/**
	 *  Move constructor. 
	 *  Initializes the unique_lock with the contents of other. 
	 */
	unique_lock(unique_lock &&other) noexcept: 
		mtx_(other.mtx_), owns_lock_(other.owns_lock_)
	{
		other.mtx_ = NULL;
		other.owns_lock_ = false;
	}

	/**
	 * Move assignment operator. 
	 * Replaces the contents with those of other using move semantics.
 	 * If prior to the call *this has an associated mutex 
 	 * and has acquired ownership of it, the mutex is unlocked. 
 	 */
	unique_lock &operator =(unique_lock &&other) noexcept
	{
		if (&other == this)
			return;

		if (mtx_ != NULL && owns_lock_)
			mtx_->unlock();

		mtx_ = other.mtx_;
		owns_lock_ = other.owns_lock_;
		other.mtx_ = NULL;
		other.owns_lock_ = false;

		return *this;
	}
#endif

	/**
	 * Destroys the lock. 
	 * If *this has an associated mutex and has acquired ownership of it, 
	 * the mutex is unlocked. 
	 */
	~unique_lock()
	{
		if (mtx_ != NULL && owns_lock_)
			mtx_->unlock();
	}

	/**
	 * Lock mutex
	 * Calls member lock of the managed mutex object.
	 */
	void lock()
	{
		mtx_->lock();
		owns_lock_ = true;
	}

	/**
	 * Lock mutex if not locked
	 * Calls member try_lock of the managed mutex object, 
	 * and uses the returned value to set the owning state.
	 */
	bool try_lock()
	{
		owns_lock_ = mtx_->try_lock();
		return owns_lock_;
	}

	/**
	 * Try to lock mutex during time span
	 * Calls member try_lock_for of the managed timed mutex object, 
	 * and uses the returned value to set the owning state.
	 */
	template <typename Rep, typename Period>
	bool try_lock_for(const chrono::duration<Rep, Period> &rel_time)
	{
		owns_lock_ = mtx_->try_lock_for(rel_time);
		return owns_lock_;
	}

	/**
	 * Try to lock mutex until time point
	 * Calls member try_lock_until of the managed timed mutex object, 
	 * and uses the returned value to set the owning state.
	 */
	template <typename Clock, typename Duration>
	bool try_lock_until(const chrono::time_point<Clock, Duration> &abs_time)
	{
		owns_lock_ = mtx_->try_lock_until(abs_time);
		return owns_lock_;
	}

	/**
	 * Unlock mutex
	 * Calls member unlock of the managed mutex object, 
	 * and sets the owning state to false.
 	 */
	void unlock()
	{
		mtx_->unlock();
		owns_lock_ = false;
	}

	/** Exchanges the internal states of the lock objects. */
	void swap(unique_lock<Mutex> &other)
	{
		std::swap(this->mtx_, other.mtx_);
		std::swap(this->owns_lock_, other.owns_lock_);
	}

	/**
	 * Breaks the association of the associated mutex, if any, and *this.
 	 * No locks are unlocked. 
 	 * If the *this held ownership of the associated mutex prior to the call, 
 	 * the caller is now responsible to unlock the mutex.
 	 */
	mutex_type *release() 
	{
		mutex_type *mtx = mtx_;
		mtx_ = NULL;
		owns_lock_ = false;
		return mtx;
	}

	/**
	 * Returns a pointer to the associated mutex, 
	 * or a null pointer if there is no associated mutex. 
	 */
	mutex_type *mutex() const { return mtx_; }

	/** 
	 * Checks whether *this owns a locked mutex or not. 
	 * true if *this has an associated mutex and has acquired ownership of it, 
	 * false otherwise. 
	 */
	bool owns_lock() const { return owns_lock_; }

	/** 
	 * Checks whether *this owns a locked mutex or not. 
	 * Return true if *this has an associated mutex 
	 * and has acquired ownership of it, false otherwise. 
	 */
#if __cplusplus >= 201103L
	explicit operator bool() const noexcept { return owns_lock_; }
#else
	typedef void (*unspecified_bool_type)();
	static void unspecified_bool_true() {}

	operator unspecified_bool_type() const 
	{
		return owns_lock_ ? unspecified_bool_true : 0; 
	}
#endif
};

/**
 * Specializes the std::swap algorithm for unique_lock. 
 * Exchanges the state of lhs with that of rhs. 
 * Effectively calls lhs.swap(rhs). 
 */
template <typename Mutex>
inline 
void swap(Hx::unique_lock<Mutex> &a, Hx::unique_lock<Mutex> &b) noexcept
{
	a.swap(b);
}

}	// namespace Hx

#endif

