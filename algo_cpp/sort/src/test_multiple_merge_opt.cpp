#include <iostream>
#include <vector>
#include <string>

#include "multiple_merge.h"

using namespace std;

void print_usage()
{
	cerr << "Usage: test_multiple_merge_opt infilelist -o outfile\n";
}

int main(int argc, char *argv[])
{
	string out_path;
	vector<string> paths;
	bool is_out_path = false;
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			if (argv[i][1] != 'o') {
				print_usage();
				exit(1);
			}
			is_out_path = true;
			continue;
		} 
		if (is_out_path) {
			out_path = argv[i];
		} else {
			paths.push_back(argv[i]);
		}
	}

	if (out_path.empty()) {
		print_usage();
		exit(1);
	}

	// print path
	cout << "input file list: ";
	for (auto &path : paths) {
		cout << path << ' ';
	}
	cout << endl;

	Hx::multiple_merge_opt<int>(paths, out_path);

	cout << "output file: " << out_path << endl;

	return 0;
}
