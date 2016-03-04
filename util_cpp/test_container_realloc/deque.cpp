#include <deque>
#include <iostream>

int main()
{
	std::deque<int> mydeque(4, 100);
	std::cout << "&mydeque[0]: " << (void *)(&mydeque[0]) << std::endl;
	int *keep = &mydeque[0];
	
	int i;
	for (i = 1; i <= 1000000; i++) {
		mydeque.push_back(i);
		if (keep != &mydeque[0]) {
			std::cout << "reallocate when push back " << i << std::endl;
			return 1;
		}
	}

	std::cout << "not reallocate" << std::endl; 

	return 0;
}

