#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "usage: a.out errno\n";
		return -1;
	}

	int errno = atoi(argv[1]);
	cout << "errno(" << errno << "): " << strerror(errno) << endl;
	return 0;
}
