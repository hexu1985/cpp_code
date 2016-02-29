// -*- C++ -*-
// HeXu's
// 2013 Aug

#include <assert.h>
#include <pthread.h>
#include "mutex.h"
#include "unique_lock.h"
#include "condition_variable.h"

namespace Hx {

namespace {

pthread_key_t notify_tss_key;
pthread_once_t notify_tss_key_flag = PTHREAD_ONCE_INIT;

struct notify_all_on_exit {
public:
	notify_all_on_exit(condition_variable *cv, mutex *m): cv_(cv), m_(m) {}
		
	~notify_all_on_exit()
	{
		m_->unlock();
		cv_->notify_all();
	}

private:
	condition_variable *cv_;
	mutex *m_;
};

extern "C" {

static void delete_notify_tss_data(void *data)
{
	delete static_cast<notify_all_on_exit *>(data);
}

static void create_notify_tss_key()
{
	int err = pthread_key_create(&notify_tss_key, delete_notify_tss_data); 
	assert(err == 0);
	(void) err;
}

}	// extern "C"

}

#if __cplusplus >= 201103L
void notify_all_at_thread_exit(condition_variable &cond, unique_lock<mutex> lck)
#else // !( __cplusplus >= 201103L )
void notify_all_at_thread_exit(condition_variable &cond, unique_lock<mutex> &lck)
#endif
{
	assert(lck.owns_lock());
	int err = pthread_once(&notify_tss_key_flag, create_notify_tss_key);
	assert(err == 0);
	(void) err;
	void *data = pthread_getspecific(notify_tss_key);
	if (!data) {
		data = new notify_all_on_exit(&cond, lck.release());
		err = pthread_setspecific(notify_tss_key, data);
		assert(err == 0);
		(void) err;
	} 
}

}	// namespace Hx
