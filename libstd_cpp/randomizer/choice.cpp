#include <cstdlib>
#include <iostream>
#include <vector>
#include "randomizer.h"

using namespace std;
using namespace Hx;

// 在[start, stop)之间, 随机生成num个实数,
// 然后循环times次, 每次随机从这num个实数中挑选一个并打印.
int main(int argc, char *argv[])
{
	if (argc != 5) {
		cerr << "usage: choice num start stop times\n";
		exit(1);
	}

	int n = atoi(argv[1]);
	double start = atof(argv[2]);
	double stop = atof(argv[3]);
	double d = stop-start;

	Randomizer random;
	vector<double> seq;
	for (int i = 0; i < n; i++) {
		seq.push_back(start+random.random()*d); 
	}

	random.srand();
	n = atoi(argv[4]);
	for (int i = 0; i < n; i++) {
		cout << random.choice(seq) << '\n';
	}

	return 0;
}

