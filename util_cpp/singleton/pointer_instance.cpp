#include "singleton.h"
#include <thread>
#include <chrono>

static Singleton *instance_;

Singleton &Singleton::GetInstance()
{
	if (instance_ == nullptr) {
		std::this_thread::yield();
		instance_ = new Singleton;
	}
	return *instance_;
}


