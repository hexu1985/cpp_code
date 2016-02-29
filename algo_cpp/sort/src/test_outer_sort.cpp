#include <iostream>
#include <vector>
#include <string>

#include "outer_sort.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " from_file to_file\n";
		exit(1);
	}

	Hx::outer_sort<int>(argv[1], argv[2]);

	return 0;
}
