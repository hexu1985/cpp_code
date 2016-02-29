#ifndef HUFFMAN_UTIL_H
#define HUFFMAN_UTIL_H

#include <vector>
#include <unordered_map>
#include <string>
#include <cstddef>
#include "huffman_tree.h"

void read(const std::string &file_name, std::vector<char> &buffer);

void write(const std::string &file_name, const std::vector<char> &buffer);

void read(const std::string &file_name, std::vector<bool> &code_list);

void write(const std::string &file_name, const std::vector<bool> &code_list);

void count(const std::vector<char> &buffer, std::unordered_map<char, size_t> &key_set);

void read(const std::string &file_name, Hx::huffman_tree<char, size_t> &huff);

void write(const std::string &file_name, const Hx::huffman_tree<char, size_t> &huff);

void print(std::ostream &out, const std::unordered_map<char, size_t> &key_set);

#endif
