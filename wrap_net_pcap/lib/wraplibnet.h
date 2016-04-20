#ifndef	WRAPLIBNET_H
#define	WRAPLIBNET_H

#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <libnet.h>
#include "net_header.h"

/**
 * 该函数初始化libnet函数库:
 * 返回一个libnet_t类型的描述符, 以备随后的构造数据报和发送数据报的函数中使用,
 * injection_type指明了发送数据报使用的接口类型, 如数据链路层或者原始套接字等,
 * Device是一个网络设备名称的字符串, 在Linux下是"eth0"等.
 */
libnet_t *Libnet_init(int injection_type, char *device);

/**
 * 地址解析, 将ipv4地址string或是host string转换成uint32_t
 */
uint32_t Libnet_name2addr4(libnet_t *l, char *host_name, uint8_t use_name);

/**
 * 数据包发送函数
 */
int Libnet_write(libnet_t *l);

/**
 * 构造响应报文的tcp部分:
 */
void Libnet_build_tcp_resp(
		struct tcphdr *tcpptr, 
		uint32_t seq,
		uint32_t ack,
		uint8_t control, 
		const uint8_t *payload,
		uint32_t payload_s,
		libnet_t *l);

/**
 * 构造响应报文的ipv4部分:
 */
void Libnet_build_ipv4_resp(
		struct ip *ipptr, 
		uint16_t ip_len,
		uint8_t prot,
		const uint8_t *payload,
		uint32_t payload_s,
		libnet_t *l);

/**
 * 构造响应报文pppoe和vlan部分:
 * 返回payload length
 */
int Libnet_build_pppoe_vlan_resp(
		uint8_t *eth_payload, 
		int buflen,
		struct Net_pppoe_hdr *pppoe, 
		struct Net_vlan_hdr *vlan, 
		int vlan_num);

/**
 * 构造响应报文的ethernet部分:
 */
void Libnet_build_ethernet_resp(
		struct ether_header *eptr,
		const uint8_t *payload,
		uint32_t payload_s,
		libnet_t *l);

#endif

