#define private public
#include "singleton.h"

static Singleton instance_;

Singleton &Singleton::GetInstance()
{
	return instance_;
}

