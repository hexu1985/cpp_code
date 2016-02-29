#include <cstdlib>
#include <cstddef>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "huffman_tree.h"
#include "huffman_util.h"

int main(int argc, char *argv[])
{
	if (argc < 2 || argc > 3) {
		std::cerr << "usage: " << argv[0] << " infile outfile\n";
		exit(1);
	}
	std::string infile_name(argv[1]);
	std::string outfile_prefix;

	if (argc == 3) {
		outfile_prefix = argv[2];
	} else {
		outfile_prefix = argv[1];
	}

	std::vector<char> file_content;
	read(infile_name, file_content);

	std::unordered_map<char, size_t> key_set;
	count(file_content, key_set);

	std::cout << "key_set:\n";
	print(std::cerr, key_set);

	Hx::huffman_tree<char, size_t> huff(key_set);
	std::cout << "huffman dictionary:\n";
	huff.print(std::cerr);

	std::vector<bool> code_content;
	huff.encode(file_content.data(), file_content.size(), code_content);
	code_content.resize((code_content.size()+7)/8*8);

	write(outfile_prefix+".huff.code", code_content);
	write(outfile_prefix+".huff.dict", huff);
	
	std::ofstream size_file(outfile_prefix+".huff.size");
	if (!size_file.good()) {
		std::cerr << "open " << outfile_prefix+".huff.size" << " fault!\n";
		exit(1);
	}
	size_file << file_content.size() << '\n';

	std::cout << '\n';
	std::cout << "huffman encode ok!\n";

	return 0;
}
