// -*- C++ -*-
// HeXu's
// 2013 Jun

#ifndef HX_THIS_THREAD_H
#define HX_THIS_THREAD_H

#include <pthread.h>
#include "key_words.h"
#include "chrono.h"
#include "thread_id.h"

namespace Hx {

namespace this_thread {

/** 
 * Returns the id of the current thread. 
 */
inline thread_id get_id() noexcept
{
	return thread_id(pthread_self());
}

/** 
 * Provides a hint to the implementation to reschedule 
 * the execution of threads, allowing other threads to run. 
 */
inline void yield() noexcept
{
	sched_yield();
}

/** wrapper function of nanosleep */
inline void sleep(const struct timespec &ts)
{
	struct timespec trq = ts, trm;
	while (true) {
		if (nanosleep(&trq, &trm) == 0)
			break;
		else if (errno == EINTR)
			trq = trm;
		else
			throw system_error(errno, system_category(), __func__);
	}
}

/**
 * Sleep for time span
 * Blocks execution of the calling thread during the span of time 
 * specified by rel_time. The execution of the current thread is stopped 
 * until at least rel_time has passed from now. 
 * Other threads continue their execution.
 */
template <typename Rep, typename Period>
void sleep_for(const chrono::duration<Rep, Period> &rel_time)
{
	if (rel_time.count() <= 0)
		return;

	struct timespec ts;
	chrono::seconds sec = chrono::duration_cast<chrono::seconds>(rel_time);
	ts.tv_sec = sec.count();
#if __cplusplus >= 201103L
	ts.tv_nsec = chrono::duration_cast<chrono::nanoseconds>(rel_time - sec).count();
#else
	ts.tv_nsec = chrono::duration_cast<chrono::nanoseconds>(
		rel_time - chrono::duration<Rep, Period>(sec)).count();
#endif

	sleep(ts);
}

/**
 * Sleep until time point
 * Blocks the calling thread until abs_time.
 * The execution of the current thread is stopped until at least abs_time, 
 * while other threads may continue to advance.
 */
template <typename Clock, typename Duration>
void sleep_until(const chrono::time_point<Clock, Duration> &abs_time)
{
	Duration rel_time = abs_time - Clock::now();
	sleep_for(rel_time);
}

}	// namespace this_thread

}	// namespace Hx

#endif
