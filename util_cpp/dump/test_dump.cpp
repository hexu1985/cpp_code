#include "dump.h"

#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " file.\n";
        return -1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cout << "open " << argv[1] << " fail\n";
        return -2;
    }

    const int BUF_SIZE = 128;
    char buf[BUF_SIZE] = {0}; 

    int n;
    while ((n = file.readsome(buf, BUF_SIZE)) > 0) {
        dump((unsigned char *) buf, n, NULL);
    }

	fflush(stdout);

    return 0;
}
