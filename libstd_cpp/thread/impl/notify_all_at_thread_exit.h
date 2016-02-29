// -*- C++ -*-
// HeXu's
// 2013 May

#ifndef HX_NOTIFY_ALL_AT_THREAD_EXIT_H
#define HX_NOTIFY_ALL_AT_THREAD_EXIT_H

#include "mutex.h"
#include "unique_lock.h"
#include "condition_variable.h"

namespace Hx {

/**
 * Notify all at thread exit
 * When the calling thread exits, all threads waiting on cond are notified 
 * to resume execution.
 */
#if __cplusplus >= 201103L
void notify_all_at_thread_exit(condition_variable &cond, unique_lock<mutex> lck);
#else // !( __cplusplus >= 201103L )
void notify_all_at_thread_exit(condition_variable &cond, unique_lock<mutex> &lck);
#endif // __cplusplus >= 201103L

}	// namespace Hx

#endif

