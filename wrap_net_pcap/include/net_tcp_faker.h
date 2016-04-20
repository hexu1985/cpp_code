#ifndef	NET_TCP_FAKER_H
#define	NET_TCP_FAKER_H

#include "net_faker_base.h"

struct tcphdr;
struct ip;
struct Net_pppoe_hdr;
struct Net_vlan_hdr;
struct ether_header;

class Net_tcp_faker: public Net_faker_base {
public:
	enum { MAX_SEND_LEN = 1400 };

	Net_tcp_faker(): Net_faker_base() {}
	Net_tcp_faker(const char *device): Net_faker_base(device) {}

	// 发送ACK|PSH报文, 发送带数据的TCP流
	int send_tcp_data(
			const char *data, int len, 
			struct tcphdr *tcpptr, 
			struct ip *ipptr, 
			struct Net_pppoe_hdr *pppoe, 
			struct Net_vlan_hdr *vlan, int vlan_num,
			struct ether_header *eptr);

	// 发送SYN|ACK报文, TCP conect 三路握手中的第二路
	int send_tcp_syn_ack(
			struct tcphdr *tcpptr, 
			struct ip *ipptr, 
			struct Net_pppoe_hdr *pppoe, 
			struct Net_vlan_hdr *vlan, int vlan_num,
			struct ether_header *eptr); 

	// 发送ACK报文
	int send_tcp_ack(
			struct tcphdr *tcpptr, 
			struct ip *ipptr, 
			struct Net_pppoe_hdr *pppoe, 
			struct Net_vlan_hdr *vlan, int vlan_num, 
			struct ether_header *eptr);

	// 发送RST报文, 针对已连接数据流
	int send_tcp_rst(
			struct tcphdr *tcpptr, 
			struct ip *ipptr, 
			struct Net_pppoe_hdr *pppoe, 
			struct Net_vlan_hdr *vlan, int vlan_num,
			struct ether_header *eptr);

	// 发送TCP RST报文, 针对SYN报文
	int send_tcp_syn_rst(
			struct tcphdr *tcpptr, 
			struct ip *ipptr, 
			struct Net_pppoe_hdr *pppoe, 
			struct Net_vlan_hdr *vlan, int vlan_num,
			struct ether_header *eptr);

	// 发送FIN|ACK报文, TCP disconect 三路握手中的第一路
	int send_tcp_fin(
			struct tcphdr *tcpptr, 
			struct ip *ipptr, 
			struct Net_pppoe_hdr *pppoe, 
			struct Net_vlan_hdr *vlan, int vlan_num,
			struct ether_header *eptr); 

	// 发送FIN|ACK报文, TCP disconect 三路握手中的第二路
	int send_tcp_fin_ack(
			struct tcphdr *tcpptr, 
			struct ip *ipptr, 
			struct Net_pppoe_hdr *pppoe, 
			struct Net_vlan_hdr *vlan, int vlan_num,
			struct ether_header *eptr); 
};

#endif
