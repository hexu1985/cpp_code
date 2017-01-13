#include <string>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;

std::vector<std::string> split(const string& s, char c) 
{
    std::vector<std::string> v;

	string::size_type i = 0;
	string::size_type j = s.find(c);

	while (j != string::npos) {
		v.push_back(s.substr(i, j-i));
		i = ++j;
		j = s.find(c, j);

		if (j == string::npos)
			v.push_back(s.substr(i, s.length( )));
	}

    return v;
}

int main(int argc, char *argv[]) 
{
	string s = "Account Name,Address 1,Address 2,City";
    if (argc == 2) {
        s = argv[1];
    }

	vector<string> v;
	v = split(s, ',');

	for (int i = 0; i < v.size( ); ++i) 
    {
		cout << v[i] << '\n';
	}
}

