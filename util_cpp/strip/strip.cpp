#include <iostream>
#include <string>

using namespace std;

string strip(const string &str)
{
    size_t beg = str.find_first_not_of(' ');
    size_t end = str.find_last_not_of(' ');
	if (beg == string::npos || end == string::npos)
		return "";
    return str.substr(beg, end-beg+1);
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cout << "usage: strip str" << endl;
		return -1;
	}

	string str = argv[1];
	cout << "orignal str: [" << str << "]\n";
	cout << "strip str: [" << strip(str) << "]\n";
	return 0;
}
