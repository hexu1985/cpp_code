#include <cstdlib>
#include <iostream>
#include "randomizer.h"

using namespace std;
using namespace Hx;

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "usage: random num\n";
		exit(1);
	}

	int n = atoi(argv[1]);
	Randomizer random;
	for (int i = 0; i < n; i++) {
		cout << random.random() << "\n";
	}

	return 0;
}
