// regex_replace example
#include <iostream>
#include <string>
#include <regex>
#include <iterator>

int main (int argc, char *argv[])
{
  if (argc != 4) {
    std::cerr << "usage: " << argv[0] << " string regex replace\n";
	return 1;
  }
  std::string s (argv[1]);
  std::regex e (argv[2]);   // matches words beginning by "sub"

  // using string/c-string (3) version:
  std::cout << std::regex_replace (s,e,argv[3]);
  std::cout << std::endl;

  return 0;
}
