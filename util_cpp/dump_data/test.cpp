#include <iostream>
#include <string>
#include <stdint.h>
#include "read_dump_data.h"
#include "dump_data.h"

using namespace std;

int main(int argc, char *argv[])
{
	string str = "0x35";
	uint8_t c = stoi(str, nullptr, 0);
	cout << "c: " << (int) c << endl;

	std::vector<uint8_t> data = read_dump_data(argv[1]);

	dump_data("data: ", (const char *) data.data(), (int) data.size());
	return 0;
}
