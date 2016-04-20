#include "net_packet.h"
#include <string.h>

void net_packet_init(struct Net_packet *pkt)
{
	memset(pkt, 0x00, sizeof (struct Net_packet));
}
