#include "read_dump_data.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

std::vector<uint8_t> read_dump_data(std::istream &in)
{
	std::vector<uint8_t> data;
	int c = 0;
	while (in >> std::hex >> c) {
//		std::cout << std::hex << c << std::endl;
		if (c > 255 || c < 0) {
			std::cerr << "data out of range\n";
			exit(1);
		}
		data.push_back((uint8_t) c);
	}
	return data;
}

std::vector<uint8_t> read_dump_data(const std::string &file_path)
{
	std::ifstream file(file_path.c_str());
	if (!file) {
		std::cerr << "open file " << file_path << " fail.\n";
		exit(1);
	}

	return read_dump_data(file);
}
