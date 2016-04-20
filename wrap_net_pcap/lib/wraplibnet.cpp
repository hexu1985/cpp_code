#include "wraplibnet.h"
#include <cassert>
#include <string>
#include <stdexcept>

using std::string;
using std::runtime_error;

libnet_t *Libnet_init(int injection_type, char *device)
{
	char errbuf[LIBNET_ERRBUF_SIZE];
	libnet_t *l = libnet_init(injection_type, device, errbuf);
	if (l == NULL) {
		throw runtime_error("Libnet_init error: "+string(errbuf));
	}
	return l;
}

uint32_t Libnet_name2addr4(libnet_t *l, char *host_name, uint8_t use_name)
{
	assert(l);

	uint32_t ip = libnet_name2addr4(l, host_name, use_name);
	if (ip == (uint32_t) -1) {
		throw runtime_error("Libnet_name2addr4 error for"
				+string(host_name)+": "+string(libnet_geterror(l)));
	}
	return ip;
}

int Libnet_write(libnet_t *l)
{
	int c = libnet_write(l);
	if (c == -1) {
		throw runtime_error("Libnet_write error: "
				+string(libnet_geterror(l)));
	}
	return c;
}

void Libnet_build_tcp_resp(
		struct tcphdr *tcpptr, 
		uint32_t seq,
		uint32_t ack,
		uint8_t control, 
		const uint8_t *payload,
		uint32_t payload_s,
		libnet_t *l)
{
	// 构造TCP Segment
	libnet_ptag_t t = libnet_build_tcp(
			ntohs(tcpptr->th_dport),               /* source port */
			ntohs(tcpptr->th_sport),               /* destination port */
			seq,                                   /* sequence number */
			ack,                                   /* acknowledgement num */
			control,                               /* control flags */
			17520,                                 /* window size */
			0,                                     /* checksum */
			0,                                     /* urgent pointer */
			LIBNET_TCP_H + payload_s,              /* TCP packet size */
			(uint8_t *) payload,                   /* payload */
			payload_s,                             /* payload size */
			l,                                     /* libnet handle */
			0);                                    /* libnet id */
	if (t == -1)
	{
		throw runtime_error("build tcp resp error: "+
				string(libnet_geterror(l)));
	}
}

void Libnet_build_ipv4_resp(
		struct ip *ipptr, 
		uint16_t ip_len,
		uint8_t prot,
		const uint8_t *payload,
		uint32_t payload_s,
		libnet_t *l)
{
	// 构造IP datagram
	libnet_ptag_t t = libnet_build_ipv4(
			ip_len,                                  /* length */
			0,                                       /* TOS */
			1691,                                    /* IP ID */
			0,                                       /* IP Frag */
			64,                                      /* TTL */
			prot,                                    /* protocol */
			0,                                       /* checksum */
			ipptr->ip_dst.s_addr,                    /* source IP */
			ipptr->ip_src.s_addr,                    /* destination IP */
			(uint8_t *) payload,                     /* payload */
			payload_s,                               /* payload size */
			l,                                       /* libnet handle */
			0);                                      /* libnet id */
	if (t == -1)
	{
		throw runtime_error("build ipv4 resp error: "+
				string(libnet_geterror(l)));
	}
}

int Libnet_build_pppoe_vlan_resp(
		uint8_t *eth_payload, 
		int buflen,
		struct Net_pppoe_hdr *pppoe, 
		struct Net_vlan_hdr *vlan, 
		int vlan_num)
{
	int eth_payload_len = 0;

	// 构造vlan header
	if (vlan != NULL) {
		assert(buflen <= (int) (vlan_num * sizeof (struct Net_vlan_hdr)));

		eth_payload_len = vlan_num * sizeof (struct Net_vlan_hdr);
		memcpy(eth_payload, (uint8_t *) vlan, eth_payload_len);
	}

	// 构造pppoe header
	if (pppoe != NULL) {
		struct Net_pppoe_hdr *ppphdr = NULL;
		unsigned short pppoe_payload_len = 0;

		assert(buflen <= (int) (eth_payload_len + sizeof (struct Net_pppoe_hdr)));

		//有PPPOE头的以太数据
		ppphdr = NULL;
		pppoe_payload_len = 0;
		pppoe_payload_len = LIBNET_TCP_H + LIBNET_IPV4_H + 2;

		ppphdr = ( struct Net_pppoe_hdr * ) (eth_payload + eth_payload_len);
		ppphdr->ver = 1;
		ppphdr->type = 1;
		ppphdr->code = 0;
		ppphdr->ssn_id = pppoe->ssn_id;
		ppphdr->length = htons (pppoe_payload_len);
		ppphdr->protocol = pppoe->protocol;

		eth_payload_len += sizeof (struct Net_pppoe_hdr);
	}

	return eth_payload_len; 
}

void Libnet_build_ethernet_resp(
		struct ether_header *eptr,
		const uint8_t *payload,
		uint32_t payload_s,
		libnet_t *l)
{
	libnet_ptag_t t = libnet_build_ethernet(
			eptr->ether_shost,                  /* ethernet destination */
			eptr->ether_dhost,                  /* ethernet source */
			ntohs(eptr->ether_type),            /* protocol type */
			(uint8_t *) payload,                /* payload */
			payload_s,                          /* payload size */
			l,                                  /* libnet handle */
			0);
	if (t == -1)
	{
		throw runtime_error("build ethernet resp error: "+
				string(libnet_geterror(l)));
	}
}
