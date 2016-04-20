#include <arpa/inet.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "usage: a.out filename\n";
		return 1;
	}

	const char *file_path = argv[1];
	ifstream ifile(file_path);
	if (!ifile) {
		throw runtime_error("open file \""+string(file_path)+
				"\" fault for load ip2clueid map");
	}

	string line;
	unsigned int ip;
	unsigned int clueid;
	while (getline(ifile, line)) {
		sscanf(line.c_str(), "%x %x", &ip, &clueid);
#ifndef	NDEBUG
		cout << "orignal, " << hex << "ip: " << ip << ", clueid: " << clueid << endl;
#endif
		in_addr addr;
		addr.s_addr = htonl(ip);
		cout << "decode, " << dec 
			<< "ip: " << inet_ntoa(addr)
			<< ", clueid: " << ntohs(short(clueid)) << endl;
	}

	return 0;
}
