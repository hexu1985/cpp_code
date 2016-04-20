#include "net_tcp_faker.h"
#include <stdint.h>
#include <algorithm>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include "net_util.h"
#include "wraplibnet.h"

using std::min;

int Net_tcp_faker::send_tcp_data(
		const char *data, int len, 
		struct tcphdr *tcpptr, 
		struct ip *ipptr, 
		struct Net_pppoe_hdr *pppoe, 
		struct Net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr) try
{
	int req_payload_len = net_cal_payload_len(tcpptr, ipptr);
	int c = 0;
	int nsend = 0; 
	uint8_t eth_payload[128] = {0};
	int eth_payload_len = 0;
	libnet_t *l = this->native_handle();

	// 构造pppoe and vlan header
	eth_payload_len = Libnet_build_pppoe_vlan_resp(
			eth_payload, sizeof (eth_payload),
			pppoe, vlan, vlan_num);

	for (int i = 0; i < len; i += nsend) {
		nsend = min<int>(MAX_SEND_LEN, len-i);

		// 构造TCP Segment
		Libnet_build_tcp_resp(
				tcpptr,
				ntohl(tcpptr->th_ack)+i,               /* sequence number */
				ntohl(tcpptr->th_seq)+req_payload_len, /* acknowledgement num */
				(TH_ACK | TH_PUSH),                    /* control flags */
				(uint8_t *) data + i,                  /* payload */
				nsend,                                 /* payload size */
				l);

		// 构造IP datagram
		Libnet_build_ipv4_resp(
				ipptr,
				LIBNET_IPV4_H + LIBNET_TCP_H + nsend,    /* length */
				IPPROTO_TCP,                             /* protocol */
				NULL,                                    /* payload */
				0,                                       /* payload size */
				l);                                      /* libnet handle */

		// 构造ethernet frame
		Libnet_build_ethernet_resp(
				eptr,
				(eth_payload_len > 0 ? eth_payload : NULL),
				eth_payload_len,
				l);

		// 发送报文
		c += Libnet_write(l);
	
		// 为下一个报文做准备
		libnet_clear_packet(l);
	}

	return c;
} catch (...) {
	libnet_clear_packet(this->native_handle());
	throw;
}

int Net_tcp_faker::send_tcp_syn_ack(
		struct tcphdr *tcpptr, 
		struct ip *ipptr, 
		struct Net_pppoe_hdr *pppoe, 
		struct Net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr) try
{
	int c;
	uint8_t eth_payload[128] = {0};
	int eth_payload_len = 0;
	libnet_t *l = this->native_handle();

	// 构造TCP Segment
	Libnet_build_tcp_resp(
			tcpptr,
			0,                                     /* sequence number */
			ntohl(tcpptr->th_seq)+1,               /* acknowledgement num */
			(TH_SYN | TH_ACK),                     /* control flags */
			NULL,                                  /* payload */
			0,                                     /* payload size */
			l);

	// 构造IP datagram
	Libnet_build_ipv4_resp(
			ipptr,
			LIBNET_IPV4_H + LIBNET_TCP_H,            /* length */
			IPPROTO_TCP,                             /* protocol */
			NULL,                                    /* payload */
			0,                                       /* payload size */
			l);                                      /* libnet handle */

	// 构造pppoe and vlan header
	eth_payload_len = Libnet_build_pppoe_vlan_resp(
			eth_payload, sizeof (eth_payload),
			pppoe, vlan, vlan_num);

	// 构造ethernet frame
	Libnet_build_ethernet_resp(
			eptr,
			(eth_payload_len > 0 ? eth_payload : NULL),
			eth_payload_len,
			l);

	// 发送报文
	c = Libnet_write(l);

	// 为下一个报文做准备
	libnet_clear_packet(l);

	return c;
} catch (...) {
	libnet_clear_packet(this->native_handle());
	throw;
}

int Net_tcp_faker::send_tcp_ack(
		struct tcphdr *tcpptr, 
		struct ip *ipptr, 
		struct Net_pppoe_hdr *pppoe, 
		struct Net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr) try 
{
	int req_payload_len = net_cal_payload_len(tcpptr, ipptr);
	int c;
	uint8_t eth_payload[128] = {0};
	int eth_payload_len = 0;
	libnet_t *l = this->native_handle();

	// 构造TCP Segment
	uint32_t ack = ntohl(tcpptr->th_seq);
	ack = (tcpptr->th_flags & (TH_SYN | TH_FIN)) ? ack+1 : ack+req_payload_len;
	Libnet_build_tcp_resp(
			tcpptr,
			ntohl(tcpptr->th_ack),                 /* sequence number */
			ack,                                   /* acknowledgement num */
			TH_ACK,                                /* control flags */
			NULL,                                  /* payload */
			0,                                     /* payload size */
			l);

	// 构造IP datagram
	Libnet_build_ipv4_resp(
			ipptr,
			LIBNET_IPV4_H + LIBNET_TCP_H,            /* length */
			IPPROTO_TCP,                             /* protocol */
			NULL,                                    /* payload */
			0,                                       /* payload size */
			l);                                      /* libnet handle */

	// 构造pppoe and vlan header
	eth_payload_len = Libnet_build_pppoe_vlan_resp(
			eth_payload, sizeof (eth_payload),
			pppoe, vlan, vlan_num);

	// 构造ethernet frame
	Libnet_build_ethernet_resp(
			eptr,
			(eth_payload_len > 0 ? eth_payload : NULL),
			eth_payload_len,
			l);

	// 发送报文
	c = Libnet_write(l);

	// 为下一个报文做准备
	libnet_clear_packet(l);

	return c;
} catch (...) {
	libnet_clear_packet(this->native_handle());
	throw;
}

int Net_tcp_faker::send_tcp_rst(
		struct tcphdr *tcpptr, 
		struct ip *ipptr, 
		struct Net_pppoe_hdr *pppoe, 
		struct Net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr) try
{
	int c;
	uint8_t eth_payload[128] = {0};
	int eth_payload_len = 0;
	libnet_t *l = this->native_handle();

	// 构造TCP Segment
	Libnet_build_tcp_resp(
			tcpptr,
			ntohl(tcpptr->th_ack),                  /* sequence number */
			0,                                      /* acknowledgement num */
			TH_RST,                                 /* control flags */
			NULL,                                   /* payload */
			0,                                      /* payload size */
			l);

	// 构造IP datagram
	Libnet_build_ipv4_resp(
			ipptr,
			LIBNET_IPV4_H + LIBNET_TCP_H,            /* length */
			IPPROTO_TCP,                             /* protocol */
			NULL,                                    /* payload */
			0,                                       /* payload size */
			l);                                      /* libnet handle */

	// 构造pppoe and vlan header
	eth_payload_len = Libnet_build_pppoe_vlan_resp(
			eth_payload, sizeof (eth_payload),
			pppoe, vlan, vlan_num);

	// 构造ethernet frame
	Libnet_build_ethernet_resp(
			eptr,
			(eth_payload_len > 0 ? eth_payload : NULL),
			eth_payload_len,
			l);

	// 发送报文
	c = Libnet_write(l);

	// 为下一个报文做准备
	libnet_clear_packet(l);

	return c;
} catch (...) {
	libnet_clear_packet(this->native_handle());
	throw;
}

int Net_tcp_faker::send_tcp_syn_rst(
		struct tcphdr *tcpptr, 
		struct ip *ipptr, 
		struct Net_pppoe_hdr *pppoe, 
		struct Net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr) try
{
	int c;
	uint8_t eth_payload[128] = {0};
	int eth_payload_len = 0;
	libnet_t *l = this->native_handle();

	// 构造TCP Segment
	Libnet_build_tcp_resp(
			tcpptr,
			0,                                      /* sequence number */
			ntohl(tcpptr->th_seq)+1,                /* acknowledgement num */
			(TH_RST | TH_ACK),                      /* control flags */
			NULL,                                   /* payload */
			0,                                      /* payload size */
			l);

	// 构造IP datagram
	Libnet_build_ipv4_resp(
			ipptr,
			LIBNET_IPV4_H + LIBNET_TCP_H,            /* length */
			IPPROTO_TCP,                             /* protocol */
			NULL,                                    /* payload */
			0,                                       /* payload size */
			l);                                      /* libnet handle */

	// 构造pppoe and vlan header
	eth_payload_len = Libnet_build_pppoe_vlan_resp(
			eth_payload, sizeof (eth_payload),
			pppoe, vlan, vlan_num);

	// 构造ethernet frame
	Libnet_build_ethernet_resp(
			eptr,
			(eth_payload_len > 0 ? eth_payload : NULL),
			eth_payload_len,
			l);

	// 发送报文
	c = Libnet_write(l);

	// 为下一个报文做准备
	libnet_clear_packet(l);

	return c;
} catch (...) {
	libnet_clear_packet(this->native_handle());
	throw;
}

int Net_tcp_faker::send_tcp_fin(
		struct tcphdr *tcpptr, 
		struct ip *ipptr, 
		struct Net_pppoe_hdr *pppoe, 
		struct Net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr) try 
{
	int req_payload_len = net_cal_payload_len(tcpptr, ipptr);
	int c;
	uint8_t eth_payload[128] = {0};
	int eth_payload_len = 0;
	libnet_t *l = this->native_handle();

	// 构造TCP Segment
	Libnet_build_tcp_resp(
			tcpptr,
			ntohl(tcpptr->th_ack),                 /* sequence number */
			ntohl(tcpptr->th_seq)+req_payload_len, /* acknowledgement num */
			(TH_FIN | TH_ACK),                     /* control flags */
			NULL,                                  /* payload */
			0,                                     /* payload size */
			l);

	// 构造IP datagram
	Libnet_build_ipv4_resp(
			ipptr,
			LIBNET_IPV4_H + LIBNET_TCP_H,            /* length */
			IPPROTO_TCP,                             /* protocol */
			NULL,                                    /* payload */
			0,                                       /* payload size */
			l);                                      /* libnet handle */

	// 构造pppoe and vlan header
	eth_payload_len = Libnet_build_pppoe_vlan_resp(
			eth_payload, sizeof (eth_payload),
			pppoe, vlan, vlan_num);

	// 构造ethernet frame
	Libnet_build_ethernet_resp(
			eptr,
			(eth_payload_len > 0 ? eth_payload : NULL),
			eth_payload_len,
			l);

	// 发送报文
	c = Libnet_write(l);

	// 为下一个报文做准备
	libnet_clear_packet(l);

	return c;
} catch (...) {
	libnet_clear_packet(this->native_handle());
	throw;
}

int Net_tcp_faker::send_tcp_fin_ack(
		struct tcphdr *tcpptr, 
		struct ip *ipptr, 
		struct Net_pppoe_hdr *pppoe, 
		struct Net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr) try
{
	int c;
	uint8_t eth_payload[128] = {0};
	int eth_payload_len = 0;
	libnet_t *l = this->native_handle();

	// 构造TCP Segment
	Libnet_build_tcp_resp(
			tcpptr,
			ntohl(tcpptr->th_ack),                 /* sequence number */
			ntohl(tcpptr->th_seq)+1,               /* acknowledgement num */
			(TH_FIN | TH_ACK),                     /* control flags */
			NULL,                                  /* payload */
			0,                                     /* payload size */
			l);

	// 构造IP datagram
	Libnet_build_ipv4_resp(
			ipptr,
			LIBNET_IPV4_H + LIBNET_TCP_H,            /* length */
			IPPROTO_TCP,                             /* protocol */
			NULL,                                    /* payload */
			0,                                       /* payload size */
			l);                                      /* libnet handle */

	// 构造pppoe and vlan header
	eth_payload_len = Libnet_build_pppoe_vlan_resp(
			eth_payload, sizeof (eth_payload),
			pppoe, vlan, vlan_num);

	// 构造ethernet frame
	Libnet_build_ethernet_resp(
			eptr,
			(eth_payload_len > 0 ? eth_payload : NULL),
			eth_payload_len,
			l);

	// 发送报文
	c = Libnet_write(l);

	// 为下一个报文做准备
	libnet_clear_packet(l);

	return c;
} catch (...) {
	libnet_clear_packet(this->native_handle());
	throw;
}

