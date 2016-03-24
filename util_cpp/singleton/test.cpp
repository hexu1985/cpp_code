#include "singleton.h"
#include <iostream>

int main()
{
	for (int i = 0; i < 10; i++) {
		Singleton::GetInstance().Sleep();
	}
	
	std::cerr << '\n';
	return 0;
}
