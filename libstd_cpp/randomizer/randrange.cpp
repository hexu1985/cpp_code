#include <cstdlib>
#include <iostream>
#include "randomizer.h"

using namespace std;
using namespace Hx;

int main(int argc, char *argv[])
{
	if (argc != 5) {
		cerr << "usage: random n start stop step\n";
		exit(1);
	}

	int n = atoi(argv[1]);
	int start = atoi(argv[2]);
	int stop = atoi(argv[3]);
	int step = atoi(argv[4]);
	Randomizer random;
	for (int i = 0; i < n; i++) {
		cout << random.randrange(start, stop, step) << "\n";
	}

	return 0;
}


