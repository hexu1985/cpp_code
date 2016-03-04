#include <vector>
#include <iostream>

int main()
{
	std::vector<int> myvector(4, 100);
	std::cout << "&myvector[0]: " << (void *)(&myvector[0]) << std::endl;
	int *keep = &myvector[0];
	
	int i;
	for (i = 1; i <= 1000000; i++) {
		myvector.push_back(i);
		if (keep != &myvector[0]) {
			std::cout << "reallocate when push back " << i << std::endl;
			keep = &myvector[0];
		}
	}

	std::cout << "not reallocate" << std::endl; 

	return 0;
}

