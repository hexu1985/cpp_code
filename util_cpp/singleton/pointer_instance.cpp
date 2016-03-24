#include "singleton.h"

static Singleton *instance_;

Singleton &Singleton::GetInstance()
{
	if (instance_ == nullptr) {
		instance_ = new Singleton;
	}
	return *instance_;
}


