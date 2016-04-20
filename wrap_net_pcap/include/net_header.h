#ifndef NET_HEADER_H
#define NET_HEADER_H

#include <stdint.h>

struct Net_vlan_hdr
{
	uint16_t id;			//优先级和ID
	uint16_t next_type;	//下一个包的以太网类型
};

/*数据包的数据结构的定义*/
struct Net_pppoe_hdr
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
	uint8_t type:4;
	uint8_t ver:4;
#elif __BYTE_ORDER == __BIG_ENDIAN
	uint8_t ver:4;
	uint8_t type:4;
#else
#error "not define __BYTE_ORDER, check it"
#endif
	uint8_t code;
	uint16_t ssn_id;
	uint16_t length;
	uint16_t protocol;
};

#endif
