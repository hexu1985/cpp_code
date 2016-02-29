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

	std::string infile_prefix(argv[1]);
	std::string outfile_name;

	if (argc == 3) {
		outfile_name = argv[2];
	} else {
		outfile_name = argv[1];
	}

	std::vector<bool> code_content;
	read(infile_prefix+".huff.code", code_content);

	Hx::huffman_tree<char, size_t> huff;
	read(infile_prefix+".huff.dict", huff);
	std::cout << "huffman dictionary:\n";
	huff.print(std::cerr);

	std::vector<char> file_content;
	huff.decode(code_content, file_content);

	std::ifstream size_file(infile_prefix+".huff.size");
	size_t size;
	if (!size_file.good()) {
		std::cerr << "open " << infile_prefix+".huff.size" << " fault!\n";
		size = file_content.size();
	}
	size_file >> size;
	size_file.close();

	file_content.resize(size);

	write(outfile_name, file_content);

	std::cout << '\n';
	std::cout << "huffman decode ok!\n";

	return 0;
}
