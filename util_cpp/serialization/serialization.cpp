#include <iostream>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <arpa/inet.h>

using namespace std;

struct Binary_pack {
	int32_t type;
	uint32_t id;
	uint16_t port;
	char name[16];
};

int serialize(uint8_t *buf, int len, const Binary_pack &in)
{
	assert(len >= sizeof (Binary_pack));
	memcpy(buf, &in, sizeof (Binary_pack));
	Binary_pack &pack = *(Binary_pack *)(buf);
	pack.type = htonl(pack.type);
	pack.id = htonl(pack.id);
	pack.port = htons(pack.port);
	return sizeof (Binary_pack);
}

const uint8_t *deserialize(Binary_pack &out, const uint8_t *buf, int len)
{
	assert(len >= sizeof (Binary_pack));
	memcpy(&out, buf, sizeof (Binary_pack));
	out.type = ntohl(out.type);
	out.id = ntohl(out.id);
	out.port = ntohs(out.port);
	return buf+sizeof (Binary_pack);
}

int main(int argc, char *argv[])
{
	Binary_pack in;
	in.type = 123;
	in.id = 456;
	in.port = 789;
	memset(in.name, 0, sizeof(in.name));
	strcpy(in.name, "hello");

	uint8_t transfer_buf[256];
	int len = serialize(transfer_buf, sizeof (transfer_buf), in);

	Binary_pack out;
	deserialize(out, transfer_buf, len);

	cout << "out.type: " << out.type << '\n';
	cout << "out.id: " << out.id << '\n';
	cout << "out.port: " << out.port << '\n';
	cout << "out.name: " << out.name << '\n';

	assert(in.type == out.type);
	assert(in.id == out.id);
	assert(in.port == out.port);
	assert(strcmp(in.name, out.name) == 0);

	return 0;
}
