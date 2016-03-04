#include <stdio.h>
#include <stdlib.h>
#include <string.h>

template <typename TypeT, typename LenT, typename ValT>
struct Basic_tlv_header {
	TypeT type;
	LenT  len;
	ValT val[];
};

typedef Basic_tlv_header<int, int, char> Tlv_header;

void usage(const char *cmd)
{
	printf("usage: %s type val\n", cmd);
}

int main(int argc, char *argv[])
{
	if (argc < 3) {
		usage(argv[0]);
		exit(1);
	}

	char buf[1024];

	// pack tlv
	Tlv_header *pack_hdr = (Tlv_header *) buf;
	pack_hdr->type = atoi(argv[1]);
	pack_hdr->len = 0;
	char *ptr = pack_hdr->val;
	for (int i = 2; i < argc; i++) {
		int len = strlen(argv[i]);
		if (pack_hdr->len + len > sizeof (buf))
			break;
		memcpy(ptr, argv[i], len);
		pack_hdr->len += len;
		ptr += len;
	}

	// unpack tlv
	Tlv_header *unpack_hdr = (Tlv_header *) buf;
	printf("type: %d\n", unpack_hdr->type);
	printf("len: %d\n", unpack_hdr->len);
	printf("val: %*.*s\n", unpack_hdr->len, unpack_hdr->len, unpack_hdr->val);

	return 0;
}
