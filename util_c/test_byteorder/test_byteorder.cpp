#include <stdint.h>
#include <iostream>

using namespace std;

union Byte_pair {
	uint16_t value;
	uint8_t bytes[2];
};

int main(int argc, char *argv[])
{
	Byte_pair byte_pair;
	byte_pair.value = 0x0102;
	if (byte_pair.bytes[0] == 0x01) {
		cout << "big byte endian" << endl;
	} else {
		cout << "little byte endian" << endl;
	}

	return 0;
}
