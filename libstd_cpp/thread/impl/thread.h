// -*- C++ -*-
// HeXu's
// 2013 Jun

#ifndef HX_THREAD_H
#define HX_THREAD_H

#include <cerrno>
#include <memory>

#if defined _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "key_words.h"
#include "functional.h"
#include "system_error.h"
#include "thread_id.h"

namespace Hx {

/**
 * The class thread represents a single thread of execution. 
 * Threads allow multiple pieces of code 
 * to run asynchronously and simultaneously. 
 */
class thread {
	thread_id id_;	// thread identify 

public:
	typedef	thread_id id;
	typedef	id::native_handle_type native_handle_type;

	/**
	 * Constructs new thread object. 
	 * Creates new thread object which does not represent a thread.
	 */
	thread() noexcept {}

#if __cplusplus >= 201103L
	thread(const thread &) = delete;
	thread &operator =(const thread &) = delete; 
#else
private:
	thread(const thread &);
	thread &operator =(const thread &other);

public:
#endif

#if __cplusplus >= 201103L
	/**
	 * Move constructor. 
	 * Constructs the thread object to represent the thread of 
	 * execution that was represented by other. 
	 * After this call other no longer represents a thread of execution.
	 */
	thread(thread &&other) noexcept: id_(other.id_) 
	{
		other.id_ = id(); 
	}

	/**
	 * Assigns the state of other to *this using move semantics. 
	 * If *this still has an associated running thread
	 * (i.e. joinable() == true), std::terminate() is called. 
	 */
	thread &operator =(thread &&other)
	{
		if (&other == this) {
			return *this;
		}

		if (joinable()) {
			std::terminate();
		}

		id_ = other.id_;
		other.id_ = id();

		return *this;
	}
#endif // __cplusplus >= 201103L

	/**
	 * Destroys the thread object. 
	 * If *this still has an associated running thread 
	 * (i.e. joinable() == true), std::terminate() is called. 
	 */
	~thread() 
	{
		if (joinable()) {
			std::terminate(); 
		}
	}

	/**
	 * Checks if the thread object identifies an active thread of execution. 
	 * Specifically, returns true if get_id() != std::thread::id(). 
	 * So a default constructed thread is not joinable. 
	 */
	bool joinable() const noexcept { return (id_ != id()); }

	/**
	 * Returns a value of thread::id identifying the thread 
	 * associated with *this. 
	 */
	id get_id() const noexcept { return id_; }

	/** 
	 * Returns the underlying implementation-defined native handle object. 
	 */
	native_handle_type native_handle() const { return id_.native_handle(); }

	/**
 	 * Returns number of concurrent threads supported by the implementation. 
 	 * The value should be considered only a hint. 
 	 */
	static unsigned hardware_concurrency()
	{
#if defined _WIN32
		SYSTEM_INFO info={{0}};
		GetSystemInfo(&info);
		return info.dwNumberOfProcessors;
#else // !( defined _WIN32 )
		int const count = sysconf(_SC_NPROCESSORS_ONLN);
		return (count>0) ? count : 0;
#endif // defined _WIN32
	}

	/**
	 * Blocks the current thread until the thread 
	 * identified by *this finishes its execution. 
	 */
	void join()
	{
		if (!joinable()) {
			throw system_error(EINVAL, system_category(), __func__);
		}

		int err = pthread_join(id_.native_handle(), NULL);
		if (err != 0) {
			throw system_error(err, system_category(), __func__);
		}
		id_ = id();
	}


	/**
	 * Separates the thread of execution from the 
	 * thread object, allowing execution to continue independently. 
	 * Any allocated resources will be freed once the thread exits.
	 */ 
	void detach()
	{
		if (!joinable()) {
			throw system_error(EINVAL, system_category(), __func__);
		}

		int err = pthread_detach(id_.native_handle());
		if (err != 0) {
			throw system_error(err, system_category(), __func__);
		}

		id_ = id();
	}

	/**
	 * If *this refers to a thread of execution, request that 
	 * the thread will be interrupted the next time it enters one of 
	 * the predefined interruption points with interruption enabled, 
	 * or if it is currently blocked in a call to one of the predefined 
	 * interruption points with interruption enabled. 
	 */
	void interrupt() 
	{
		pthread_cancel(id_.native_handle()); 
	}

	/** Exchanges the underlying handles of two thread objects. */
	void swap(thread &other) noexcept { id_.swap(other.id_); }

public:
	// Simple base type that the templatized, derived class containing
	// an arbitrary functor can be converted to and called.
	struct routine_base {
		virtual ~routine_base() {}
		virtual void run() = 0;
	};

	template <typename Fn>
	struct routine: public routine_base {
#if __cplusplus >= 201103L
		routine(Fn &&fn): f_(std::forward<Fn>(fn)) {}
#else // !( __cplusplus >= 201103L )
		routine(Fn fn): f_(fn) {}
#endif // __cplusplus >= 201103L

		virtual void run() { f_(); }

		Fn f_;
	};

#if __cplusplus >= 201103L
	template <typename Fn, typename ...Args>
	explicit thread(Fn &&fn, Args &&...args)
	{
		create_thread(make_routine(std::bind(
			std::forward<Fn>(fn), std::forward<Args>(args)...)));
	}
#else // !( __cplusplus >= 201103L )
	template <typename Fn>
	explicit thread(Fn fn)
	{
		create_thread(make_routine(fn));
	}

	template <typename Fn, typename A1>
	explicit thread(Fn fn, A1 a1)
	{
		create_thread(make_routine(std::bind(fn, a1)));
	}

	template <typename Fn, typename A1, typename A2>
	explicit thread(Fn fn, A1 a1, A2 a2)
	{
		create_thread(make_routine(std::bind(fn, a1, a2)));
	}

	template <typename Fn, typename A1, typename A2, typename A3>
	explicit thread(Fn fn, A1 a1, A2 a2, A3 a3)
	{
		create_thread(make_routine(std::bind(fn, a1, a2, a3)));
	}

	template <typename Fn, typename A1, typename A2, typename A3, typename A4>
	explicit thread(Fn fn, A1 a1, A2 a2, A3 a3, A4 a4)
	{
		if (joinable())
			std::terminate();

		create_thread(make_routine(std::bind(fn, a1, a2, a3, a4)));
	}
#endif // __cplusplus >= 201103L

private:
	void create_thread(routine_base *rtn)
	{
		pthread_t tid;
		int err = pthread_create(&tid, NULL, &execute_routine, rtn);
		if (err != 0) {
			delete rtn;
			throw system_error(err, system_category(), __func__);
		}
		id_ = tid;
	}

	static void *execute_routine(void *arg)
	{
		// run thread routine
		routine_base *rtn = reinterpret_cast<routine_base *>(arg);
		try 
		{
			rtn->run();
		} 
		catch (...) 
		{
			delete rtn;
			throw;
		}
		delete rtn;
		return NULL;
	}

#if __cplusplus >= 201103L
	template <typename Fn>
	inline
	routine<Fn> *make_routine(Fn &&fn)
	{
		// Create and allocate full data structure, not base.
		return new routine<Fn>(std::forward<Fn>(fn));
	}
#else // !( __cplusplus >= 201103L )
	template <typename Fn>
	inline
	routine<Fn> *make_routine(Fn fn)
	{
		// Create and allocate full data structure, not base.
		return new routine<Fn>(fn);
	}
#endif // __cplusplus >= 201103L
};

/**
 * Specializes the std::swap algorithm for thread. 
 * Exchanges the state of lhs with that of rhs. 
 * Effectively calls lhs.swap(rhs). 
 */
inline 
void swap(Hx::thread &a, Hx::thread &b) noexcept
{
	a.swap(b);
}

}	// namespace Hx

#endif // HX_THREAD_H

