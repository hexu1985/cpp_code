#ifndef __read_dump_data_h
#define __read_dump_data_h

#include <vector>
#include <string>
#include <stdint.h>
#include <iostream>

std::vector<uint8_t> read_dump_data(const std::string &file_path);
std::vector<uint8_t> read_dump_data(std::istream &in);

#endif
