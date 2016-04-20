#ifndef NET_PACKET_H
#define NET_PACKET_H

#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <sys/time.h>
#include "net_header.h"

struct Net_packet
{
	enum { MAX_FRAME_LEN = 1620 };
	struct ether_header         *hdr_ether;		//以太网报首
	struct Net_vlan_hdr         *hdr_vlan;		//vlan头
	int							vlan_num;		//vlan头层数
	struct Net_pppoe_hdr 		*hdr_pppoe;		//pppoe报首
	struct ip                   *hdr_ip;		//网络层报首
	struct ip6_hdr              *hdr_ip6;
	struct tcphdr               *hdr_tcp;		//传输层报首
	struct udphdr               *hdr_udp;
	uint8_t					    *hdr_body;		//数据包体的指针
	int							body_len;		//数据包除去头部分体的长度

	struct timeval	pkt_ts;						//数据包抓取的时间戳
	uint16_t		pkt_len;					//数据包抓取到的总长, 包含头
	uint8_t			pkt_data[MAX_FRAME_LEN];	//数据存储区
};

struct Net_protocol_info;
struct pcap_pkthdr;

// 初始化Net_packet
void net_packet_init(struct Net_packet *pkt);

#endif
