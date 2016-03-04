#include <vector>
#include <iostream>

int main()
{
	std::vector<int> myvector(4, 100);
	std::cout << "&myvector[0]: " << (void *)(&myvector[0]) << std::endl;
	int *keep = &myvector[0];
	
	int n;
	while (true) {
		std::cout << "entry a number to resize: " << std::endl;
		std::cin >> n;
		myvector.resize(n);
		if (keep != &myvector[0]) {
			std::cout << "reallocate when resize " << n << std::endl;
			keep = &myvector[0];
		} else {
			std::cout << "not reallocate when resize " << n << std::endl;
		}
	}

	return 0;
}
