/* Simple TCP sniffer
 * To compile: gcc udpsniffer.c -o udppsniffer -lpcap
 * Run as root!
 * */
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include "net_sniffer.h"
#include "net_parser.h"
#include <stdexcept>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) try
{
	struct pcap_pkthdr *pkthdr;
	const unsigned char *packet = NULL;
	struct ip *ipptr = NULL;
	struct udphdr *udpptr = NULL;

	if (argc != 2){
		printf("Usage: udpsniffer <interface/pcapfile>\n");
		exit(1);
	}

	Net_sniffer sniffer;
	sniffer.open(argv[1]);

	if (sniffer.datalink_type() != DLT_EN10MB) {
		printf("not support datalink type!");
		exit(1);
	}

	Net_parser parser;
	Net_protocol_info info;

	while (1){
		sniffer.next_packet(&pkthdr, &packet);

		if (!parser.parse_packet(&info, packet, pkthdr->caplen)) {
			cout << parser.error_message() << endl;
			continue;
		}

		if (info.inet_type != Net_protocol_info::INET_IPV4) {
			cout << "not ipv4 packet" << endl;
			continue;
		}

		ipptr = (struct ip *)(packet + info.inet_off);
		printf("\n\nReceived Packet Size: %d bytes\n", pkthdr->len);
		printf("\n\nthe IP packets version: %d\n", ipptr->ip_v); 
		printf ("the IP packets total_length is :%d\n", ntohs(ipptr->ip_len));
		printf ("the IP protocol is %d\n", ipptr->ip_p);
		printf ("Destination IP: %s\n", inet_ntoa(ipptr->ip_dst));    
		printf ("Source IP: %s\n", inet_ntoa(ipptr->ip_src));

		if (info.trans_type != Net_protocol_info::TRANS_UDP) {
			cout << "not udp packet" << endl;
			continue;
		}

		udpptr = (struct udphdr *) (packet + info.trans_off);
		printf ("Destination port : %d\n", ntohs(udpptr->uh_dport));
		printf ("Source port : %d\n", ntohs(udpptr->uh_sport));
		printf ("the len of udp packet is %u\n", ntohs(udpptr->uh_ulen));
	}
	return 0;
} catch (const runtime_error &e) {
	printf("%s\n", e.what());
	return 1;
}
