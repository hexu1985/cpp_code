#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	string src = "http://www.sina.com/index.html";
	string dst = "";
	for (int i = 0; i < src.size(); i++) {
		if (src[i] == '/')
			dst += "\\/";
		else
			dst.push_back(src[i]);
	}

	cout << "src: " << src << endl;
	cout << "dst: " << dst << endl;

	return 0;
}

