
/**
 * Exit this thread.
 * The rval_ptr is a typeless pointer, similar to the single argument passed 
 * to the start routine. This pointer is available to other threads in
 * the process by calling the thread::join function.
 */
inline void exit(void *value_ptr = NULL) noexcept
{
	return pthread_exit(value_ptr);
}

/**
 * If id refers to a thread of execution, request that the thread will 
 * be interrupted the next time it enters one of the predefined interruption 
 * points with interruption enabled, or if it is currently blocked in a call 
 * to one of the predefined interruption points with interruption enabled. 
 */
inline void interrupt(const thread_id &id)
{
	pthread_cancel(id.native_handle());
}

/**
 * Check to see if the current thread has been interrupted. When you call 
 * interruption_point, if a interruption request is pending and if interruption 
 * has not been disabled, the thread will be interrupted. When interruption 
 * is disabled, however, calls to interruption_point have no effect.
 */
inline void interruption_point() 
{
	pthread_testcancel();
}

/**
 * The interruption state attribute can be either enabled or disabled. 
 * A thread can change its interruptability state by calling 
 * interruption_state::set_disable or interruption_state::set_enable.
 * A thread starts with a default interruption state of enabled. 
 * When the state is set to disabled, a call to thread::interrupt will not 
 * kill the thread. Instead, the interruption request remains pending 
 * for the thread. When the state is enabled again, the thread will act 
 * on any pending interruption requests at the next interrupiont point.
 */
class interruption_state {
public:
	interruption_state(): 
		is_set_(false), old_state_(PTHREAD_CANCEL_ENABLE) {}

	~interruption_state()
	{
		if (is_set_)
			pthread_setcancelstate(old_state_, NULL);
	}

	/** disable this thread to be interrupted */
	void set_disable()
	{
		int state;
		int err = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &state);
		if (err != 0)
			throw system_error(err, system_category(), 
				"interruption_state::set_disable");
		if (!is_set_) {
			old_state_ = state;
			is_set_ = true;
		}
	}

	/** enable this thread to be interrupted */
	void set_enable()
	{
		int state;
		int err = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &state);
		if (err != 0)
			throw system_error(err, system_category(), 
				"interruption_state::set_enable");
		if (!is_set_) {
			old_state_ = state;
			is_set_ = true;
		}
	}

	/** restore old state of this thread's interruption state */
	void reset()
	{
		int err;
		if (is_set_) {
			if ((err = pthread_setcancelstate(old_state_, NULL)) != 0)
				throw system_error(err, system_category(), 
					"interruption_state::reset");
			is_set_ = false;
		}
	}

#if __cplusplus >= 201103L
	interruption_state(const interruption_state &) = delete;
	interruption_state &operator =(const interruption_state &) = delete;
#else
private:
	interruption_state(const interruption_state &);
	interruption_state &operator =(const interruption_state &);
public:
#endif

private:
	bool is_set_;
	int old_state_;
};

class disable_interruption {
public:
	disable_interruption()
	{
		state_.set_disable();
	} 

private:
	interruption_state state_;
};

/**
 * The default interruption type we have been describing is known as 
 * deferred interruption. After a call to thread::interrupt, the actual
 * interruption doesn't occur until the thread hits a interruption point. 
 * We can change the interruption type by calling 
 * interruption_type::set_deferred or interruption_type::set_asynchronous.
 * Asynchronous interruption differs from deferred interruption in that 
 * the thread can be interrupted at any time. The thread doesn't
 * necessarily need to hit a interrruption point for it to be interrupted.
 */
class interruption_type {
public:
	interruption_type(): 
		is_set_(false), old_type_(PTHREAD_CANCEL_ENABLE) {}

	~interruption_type()
	{
		if (is_set_)
			pthread_setcanceltype(old_type_, NULL);
	}

	/** set this thread interruption type asynchronous */
	void set_asynchronous()
	{
		int type;
		int err = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &type);
		if (err != 0)
			throw system_error(err, system_category(), 
				"interruption_type::set_asynchronous");
		if (!is_set_) {
			old_type_ = type;
			is_set_ = true;
		}
	}


	/** set this thread interruption type deffered */
	void set_deferred()
	{
		int type;
		int err = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &type);
		if (err != 0)
			throw system_error(err, system_category(), 
				"interruption_type::set_deferred");
		if (!is_set_) {
			old_type_ = type;
			is_set_ = true;
		}
	}

	/** restore old type of this thread's interruption type */
	void reset()
	{
		int err;
		if (is_set_) {
			if ((err = pthread_setcanceltype(old_type_, NULL)) != 0)
				throw system_error(err, system_category(), 
					"interruption_type::reset");
			is_set_ = false;
		}
	}

#if __cplusplus >= 201103L
	interruption_type(const interruption_type &) = delete;
	interruption_type &operator =(const interruption_type &) = delete;
#else
private:
	interruption_type(const interruption_type &);
	interruption_type &operator =(const interruption_type &);
public:
#endif

private:
	bool is_set_;
	int old_type_;
};

class asynchronous_interruption {
public:
	asynchronous_interruption()
	{
		type_.set_asynchronous();
	} 

private:
	interruption_type type_;
};

