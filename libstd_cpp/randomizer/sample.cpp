#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include "randomizer.h"

using namespace std;
using namespace Hx;

int main(int argc, char *argv[])
{
	if (argc != 5) {
		cerr << "usage: sample num str_len_min str_len_max times\n";
		exit(1);
	}

	int n = atoi(argv[1]);
	int str_len_min = atoi(argv[2]);
	int str_len_max = atoi(argv[3]);

	string char_set = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";

	Randomizer random;
	vector<int> len_vec;
	for (int i = 0; i < n; i++) {
		len_vec.push_back(random.randint(str_len_min, str_len_max));
	}

	random.srand();
	vector<string> str_seq;
	for (int i = 0; i < n; i++) {
		str_seq.push_back(random.sample(char_set, len_vec[i]));
	}

	random.srand();
	n = atoi(argv[4]);
	for (int i = 0; i < n; i++) {
		cout << random.choice(str_seq) << '\n';
	}

	return 0;
}
