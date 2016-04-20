#include "net_parser.h"
#include <assert.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include "net_header.h"

namespace {

inline std::string to_string(int val)
{
	const int sz = 16;
	char buf[sz];
	sprintf(buf, "%d", val);
	buf[sz-1] = '\0';
	return buf;
}

inline std::string to_string_hex(int val)
{
	const int sz = 16;
	char buf[sz];
	sprintf(buf, "0x%04x", val);
	buf[sz-1] = '\0';
	return buf;
}

}	// namespace 

bool Net_parser::parse_packet(Net_protocol_info *info, 
		const uint8_t *packet, int pktlen)
{
	// 重置info
	net_protocol_info_init(info);

	// 记录报文头偏移量
	int next_index = 0;

	// 解析以太网报头
	struct ether_header *eptr = (struct ether_header *) packet;
	info->ether_off = 0;	// 设置ether header offset
	next_index = sizeof (struct ether_header);
	assert(next_index <= pktlen);

	//解析vlan tag, 如果有的话
	uint16_t type = ntohs(eptr->ether_type);
	struct Net_vlan_hdr *vlan = NULL;
	int vlan_num = 0;
	if (type == 0x8100 || type == 0x9100) {
		vlan_num = 1;
		vlan = (struct Net_vlan_hdr *) (packet+next_index);
		info->vlan_off = next_index;	// 设置首vlan tag offset
		type = ntohs(vlan->next_type);
		next_index += sizeof (struct Net_vlan_hdr);
		assert(next_index <= pktlen);
	}

	// 处理多层vlan tag情况
	while (type == 0x8100 || type == 0x9100) {
		vlan_num++;
		vlan = (struct Net_vlan_hdr *) (packet+next_index);
		type = ntohs(vlan->next_type);
		next_index += sizeof (struct Net_vlan_hdr);
		assert(next_index <= pktlen);
	}
	info->vlan_num = vlan_num;	// 设置vlan tag个数

	// 解析pppoe, ipv4/ipv6 header
	struct Net_pppoe_hdr *pppoe = NULL;
	struct ip *ipptr = NULL;
	int payload_len = 0;		// 网络层上层协议有效载荷长度
	int proto = 0;		// 传输层协议类型
	switch (type) {
	case 0x0800:	// ipv4
		ipptr = (struct ip *) (packet+next_index);
		info->inet_type = Net_protocol_info::INET_IPV4;	// 设置网络层协议类型
		info->inet_off = next_index;	// 设置网络层协议头偏移量
		payload_len = ntohs(ipptr->ip_len) - ipptr->ip_hl*4;
		proto = ipptr->ip_p;
		next_index += ipptr->ip_hl*4;
		assert(next_index <= pktlen);
		break;
	case 0x8864:	// pppoe
		pppoe = (struct Net_pppoe_hdr *) (packet+next_index);
		info->pppoe_off = next_index;	// 设置pppoe header offset
		next_index += sizeof (struct Net_pppoe_hdr);
		assert(next_index <= pktlen);
		switch (ntohs(pppoe->protocol)) {
		case 0x0021:
			ipptr = (struct ip *) (packet+next_index);
			info->inet_type = Net_protocol_info::INET_IPV4;	// 设置网络层协议类型
			info->inet_off = next_index;	// 设置网络层协议头偏移量
			payload_len = ntohs(ipptr->ip_len) - ipptr->ip_hl*4;
			proto = ipptr->ip_p;
			next_index += ipptr->ip_hl*4;
			assert(next_index <= pktlen);
			break;
		default:
			m_errmsg = "not support network layer protocol type over pppoe: "
				+to_string_hex(ntohs(pppoe->protocol));
			return false;
		}
		break;
	default:
		m_errmsg = "not support network layer protocol type: "
			+to_string_hex(type);
		return false;
	}

	// 解析tcp/udp header
	struct tcphdr *tcpptr = NULL; 
	struct udphdr *udpptr = NULL; 
	switch (proto) {
	case 6:	// tcp
		tcpptr = (struct tcphdr *) (packet+next_index);
		info->trans_type = Net_protocol_info::TRANS_TCP;	// 设置传输层协议类型
		info->trans_off = next_index;	// 设置传输层协议头偏移量
		payload_len -= tcpptr->th_off*4; 
		next_index += tcpptr->th_off*4;
		assert(next_index <= pktlen);
		break;
	case 17: // udp
		udpptr = (struct udphdr *) (packet+next_index);	
		info->trans_type = Net_protocol_info::TRANS_UDP;	// 设置传输层协议类型
		info->trans_off = next_index;	// 设置传输层协议头偏移量
		payload_len = ntohs(udpptr->uh_ulen);
		next_index += sizeof (struct udphdr);
		assert(next_index <= pktlen);
		break;
	default:
		m_errmsg = "not support transport layer protocol type: "
				+to_string(proto);
		return false;
	};

	// 设置payload相关信息
	info->payload_off = next_index;
	info->payload_len = payload_len;

	return true;
}

