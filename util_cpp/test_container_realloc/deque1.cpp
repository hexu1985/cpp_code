#include <deque>
#include <iostream>

int main()
{
	std::deque<int> mydeque(4, 100);
	std::cout << "&mydeque[0]: " << (void *)(&mydeque[0]) << std::endl;
	int *keep = &mydeque[0];
	
	int n;
	while (true) {
		std::cout << "entry a number to resize: " << std::endl;
		std::cin >> n;
		mydeque.resize(n);
		if (keep != &mydeque[0]) {
			std::cout << "reallocate when resize " << n << std::endl;
			keep = &mydeque[0];
		} else {
			std::cout << "not reallocate when resize " << n << std::endl;
		}
	}

	return 0;
}
