#include "singleton.h"

Singleton &Singleton::GetInstance()
{
	static Singleton instance_;
	return instance_;
}

