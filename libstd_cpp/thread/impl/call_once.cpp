// -*- C++ -*-
// HeXu's
// 2013 Aug
// modify from boost/libs/thread/src/pthread/once.cpp

// Copyright (C) 2007 Anthony Williams
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <signal.h>
#include <stdint.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include "call_once.h"

namespace Hx {

namespace detail {

sig_atomic_t once_global_epoch = SIG_ATOMIC_MAX;
pthread_mutex_t once_epoch_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t once_epoch_cv = PTHREAD_COND_INITIALIZER;

namespace {

pthread_key_t epoch_tss_key;
pthread_once_t epoch_tss_key_flag = PTHREAD_ONCE_INIT;

extern "C" {

static void delete_epoch_tss_data(void* data)
{
	free(data);
}

static void create_epoch_tss_key()
{
	int err = pthread_key_create(&epoch_tss_key, delete_epoch_tss_data);
	assert(err == 0);
	(void) err;
}

}	// extern "C"

}

sig_atomic_t &get_once_per_thread_epoch()
{
	int err = pthread_once(&epoch_tss_key_flag, create_epoch_tss_key);
	assert(err == 0);
	(void) err;
	void* data = pthread_getspecific(epoch_tss_key);
	if(!data) {
		data = malloc(sizeof(sig_atomic_t));
		err = pthread_setspecific(epoch_tss_key, data);
		assert(err == 0);
		(void) err;
		*static_cast<sig_atomic_t*>(data) = SIG_ATOMIC_MAX;
	}
	return *static_cast<sig_atomic_t*>(data);
}

}	// namespace detail

}	// namespace Hx

