#ifndef NET_UTIL_H
#define NET_UTIL_H

#include <stdint.h>

struct pcap_pkthdr;
struct ip;
struct tcphdr;
struct Net_packet;
struct Net_protocol_info;

// 判断报文是否截断
bool net_packet_is_truncate(const struct pcap_pkthdr *hdr);

// 构造Net_packet
void net_packet_fill(struct Net_packet *pkt, 
		const uint8_t *data, const struct pcap_pkthdr *hdr,
		const struct Net_protocol_info *info);

// 计算有效载荷长度
int net_cal_payload_len(const struct tcphdr *tcpptr, const struct ip *ipptr);

#endif
