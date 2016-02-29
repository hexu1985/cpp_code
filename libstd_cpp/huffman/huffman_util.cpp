#include <cassert>
#include <cstdlib>
#include <cctype>
#include <cstdio>

#include <queue>
#include <fstream>
#include <iostream>

#include "huffman_util.h"

namespace {

void push_back(std::vector<bool> &code_list, char code)
{
	for (int i = 8-1; i >= 0; i--) {
		code_list.push_back((code >> i) & 0x01);
	} 
}

char to_char(const std::vector<bool> &code_list, size_t pos)
{
	char c = '\0';
	for (int i = 8-1; i >= 0; i--) {
		if (code_list.at(pos) == true)
			c |= (0x01 << i);
		pos++;
	}
	return c;
}

}

void read(const std::string &file_name, std::vector<char> &buffer)
{
	std::ifstream ifile;
	ifile.open(file_name);
	if (!ifile.good()) {
		std::cerr << "open " << file_name << " fault!\n";
		exit(1);
	}

	int c;
	while ((c = ifile.get()) != EOF) {
		buffer.push_back(c);
	}

	ifile.close();
	return;
}

void write(const std::string &file_name, const std::vector<char> &buffer)
{
	std::ofstream ofile;
	ofile.open(file_name);
	if (!ofile.good()) {
		std::cerr << "open " << file_name << " fault!\n";
		exit(1);
	}

	ofile.write(buffer.data(), buffer.size());
	ofile.close();
	return;
}

void read(const std::string &file_name, std::vector<bool> &code_list)
{
	std::ifstream ifile;
	ifile.open(file_name);
	if (!ifile.good()) {
		std::cerr << "open " << file_name << " fault!\n";
		exit(1);
	}

	int c;
	while ((c = ifile.get()) != EOF) {
		push_back(code_list, c);
	}
	ifile.close();
	return;
}

void write(const std::string &file_name, const std::vector<bool> &code_list)
{
	std::ofstream ofile;
	ofile.open(file_name);
	if (!ofile.good()) {
		std::cerr << "open " << file_name << " fault!\n";
		exit(1);
	}

	size_t len = code_list.size();
	if (len % 8 != 0) {
		std::cerr << "code_list's size must be div by 8, size: " << len << '\n';
		exit(1);
	}

	for (size_t pos = 0; pos < len; pos += 8) {
		ofile.put(to_char(code_list, pos));
	}
	ofile.close();
	return;
}

void count(const std::vector<char> &buffer, std::unordered_map<char, size_t> &key_set)
{
	size_t n = buffer.size();
	for (size_t i = 0; i < n; ++i) {
		++key_set[buffer[i]];
	}
	return;
}

void read(const std::string &file_name, Hx::huffman_tree<char, size_t> &huff)
{
	std::ifstream ifile;
	ifile.open(file_name);
	if (!ifile.good()) {
		std::cerr << "open " << file_name << " fault!\n";
		exit(1);
	}

	huff.read(ifile);
	ifile.close();

	return;
}

void write(const std::string &file_name, const Hx::huffman_tree<char, size_t> &huff)
{
	std::ofstream ofile;
	ofile.open(file_name);
	if (!ofile.good()) {
		std::cerr << "open " << file_name << " fault!\n";
		exit(1);
	}

	huff.write(ofile);
	ofile.close();
	return;
}

void print(std::ostream &out, const std::unordered_map<char, size_t> &key_set)
{
	std::unordered_map<char, size_t>::const_iterator pos, end;
	pos = key_set.begin();
	end = key_set.end();
	for ( ; pos != end; ++pos) {
		out << (int) pos->first << '('
			<< (isalnum(pos->first) ? pos->first : '.') 
			<< "):" << pos->second << '\n';
	}

	return;
}

