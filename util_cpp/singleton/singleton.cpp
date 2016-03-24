#include "singleton.h"

#include <iostream>
#include <thread>
#include <chrono>

Singleton::Singleton()
{
	std::cerr << "Singleton::Singleton()\n";
}

Singleton::~Singleton()
{
	std::cerr << "Singleton::~Singleton()\n";
}


void Singleton::Sleep() {
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cerr << '.';
}
