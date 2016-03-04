#include <string>
#include <iostream>

using namespace std;

int main()
{
	string str(100, '\0');

	cout << "str.size(): " << str.size() << endl;

	//str.append("\r\n\r\n\0abcdef");
	str.append("\r\n\r\n\0abcdef", 11);

	size_t pos = str.find(string("\r\n\r\n", 4));
	if (pos != string::npos) {
		cout << "found \\r\\n\\r\\n at: " << pos << endl;
	} else {
		cout << "not found \\r\\n\\r\\n" << endl;
	}

	pos = str.find(string("abc"));
	if (pos != string::npos) {
		cout << "found abc at: " << pos << endl;
	} else {
		cout << "not found abc " << endl;
	}

	return 0;
}

