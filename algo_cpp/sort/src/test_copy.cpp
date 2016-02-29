#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " from_file to_file\n";
		exit(1);
	}

	ifstream ifile(argv[1]);
	if (!ifile) {
		cerr << "open file: " << argv[1] << " error\n";
		exit(1);
	}

	ofstream ofile(argv[2]);
	if (!ofile) {
		cerr << "open file: " << argv[2] << " error\n";
		exit(1);
	}

	ofile << ifile.rdbuf();

	return 0;
}
