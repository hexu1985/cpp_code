#include "net_util.h"
#include <pcap.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <assert.h>
#include <string.h>
#include <stdexcept>
#include "net_packet.h"
#include "net_protocol_info.h"

using std::runtime_error;

bool net_packet_is_truncate(const pcap_pkthdr *pkthdr)
{
	// caplen为抓取的报文长度
	// len为原始报文的长度
	assert(pkthdr->caplen <= pkthdr->len);
	return (pkthdr->caplen != pkthdr->len);
}

void net_packet_fill(struct Net_packet *pkt, 
		const uint8_t *data, const struct pcap_pkthdr *hdr,
		const struct Net_protocol_info *info)
{
	// 检查报文是否截断
	if (Net_packet::MAX_FRAME_LEN  < hdr->caplen) {
		throw runtime_error("packet is larger than MAX_FRAME_LEN");
	}

	// 初始化Net_packet
	net_packet_init(pkt);

	// 复制数据部分
	pkt->pkt_ts = hdr->ts;						//数据包抓取的时间戳
	pkt->pkt_len = hdr->caplen;					//数据包抓取到的总长, 包含头
	memcpy(pkt->pkt_data, data, hdr->caplen);	//数据存储区

	//以太网报首
	if (info->ether_off != Net_protocol_info::OFFSET_INVALID) {
		pkt->hdr_ether = (struct ether_header *) (pkt->pkt_data + info->ether_off);
	} 

	//vlan头
	if (info->vlan_off != Net_protocol_info::OFFSET_INVALID) {
		pkt->hdr_vlan = (struct Net_vlan_hdr *) (pkt->pkt_data + info->vlan_off);
	}
	pkt->vlan_num = info->vlan_num;		//vlan头层数

	//pppoe报首
	if (info->pppoe_off != Net_protocol_info::OFFSET_INVALID) { 
		pkt->hdr_pppoe = (struct Net_pppoe_hdr *) (pkt->pkt_data + info->pppoe_off);
	}

	//网络层报首
	switch (info->inet_type) {
	case Net_protocol_info::INET_IPV4:
		pkt->hdr_ip = (struct ip *) (pkt->pkt_data + info->inet_off);
		break;
	case Net_protocol_info::INET_IPV6:
		pkt->hdr_ip6 = (struct ip6_hdr *) (pkt->pkt_data + info->inet_off);
		break;
	case Net_protocol_info::INET_INVALID:
		break;
	default:	//如果走到这个分支, 说明程序有bug
		assert(false);
	}

	//传输层报首
	switch (info->trans_type) {
	case Net_protocol_info::TRANS_TCP:
		pkt->hdr_tcp = (struct tcphdr *) (pkt->pkt_data + info->trans_off);
		break;
	case Net_protocol_info::TRANS_UDP:
		pkt->hdr_udp = (struct udphdr *) (pkt->pkt_data + info->trans_off);
		break;
	case Net_protocol_info::INET_INVALID:
		break;
	default:	//如果走到这个分支, 说明程序有bug
		assert(false);
	}

	//数据包体的指针
	if (info->payload_off != Net_protocol_info::OFFSET_INVALID) {  
		pkt->hdr_body = (pkt->pkt_data + info->payload_off);
	}
	pkt->body_len = info->payload_len;		//数据包除去头部分体的长度
}

// 计算有效载荷长度
int net_cal_payload_len(
		const struct tcphdr *tcpptr,
		const struct ip *ipptr)
{
	assert(ipptr); assert(tcpptr);
	return ntohs(ipptr->ip_len)-ipptr->ip_hl*4-tcpptr->th_off*4;
}
