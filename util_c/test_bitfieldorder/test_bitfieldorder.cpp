#include <stdint.h>
#include <iostream>

using namespace std;

union Bitfield_pair {
	uint8_t value;
	struct {
		uint8_t _1:4;
		uint8_t _2:4;
	} bitfield;
};

int main(int argc, char *argv[])
{
	Bitfield_pair bitfield_pair;
	bitfield_pair.value = 0x12;
	if (bitfield_pair.bitfield._1 == 1) {
		cout << "big fieldbit endian" << endl;
	} else {
		cout << "little fieldbit endian" << endl;
	}

	return 0;
}
