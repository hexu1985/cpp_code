#include <cstdlib>
#include <iostream>
#include "randomizer.h"

using namespace std;
using namespace Hx;

int main(int argc, char *argv[])
{
	if (argc != 4) {
		cerr << "usage: random n start stop\n";
		exit(1);
	}

	int n = atoi(argv[1]);
	int a = atoi(argv[2]);
	int b = atoi(argv[3]);
	Randomizer random;
	for (int i = 0; i < n; i++) {
		cout << random.randint(a, b) << "\n";
	}

	return 0;
}

