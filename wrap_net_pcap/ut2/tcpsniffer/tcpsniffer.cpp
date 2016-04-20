/* Simple TCP sniffer
 * To compile: gcc tcpsniffer.c -o tcppsniffer -lpcap
 * Run as root!
 * */
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> /* includes net/ethernet.h */
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include "net_sniffer.h"
#include <stdexcept>

using namespace std;

int main(int argc, char *argv[]) try
{
	struct pcap_pkthdr *pkthdr;
	const unsigned char *packet = NULL;
	struct iphdr *ipptr = NULL;
	struct tcphdr *tcpptr = NULL;
	struct in_addr addr;

	if (argc != 2){
		printf("Usage: ipsniffer <interface>\n");
		exit(1);
	}

	Net_sniffer sniffer;
	sniffer.open(argv[1]);
	sniffer.set_filter("tcp");

	if (sniffer.datalink_type() != DLT_EN10MB) {
		printf("not support datalink type!");
		exit(1);
	}

	while (1){
		sniffer.next_packet(&pkthdr, &packet);

		ipptr = (struct iphdr *)(packet + 14);
		printf("\n\nReceived Packet Size: caplen(%d), len(%d) bytes\n", 
				pkthdr->caplen, pkthdr->len);
		printf("\n\nthe IP packets version: %d\n", ipptr->version); 
		printf ("the IP packets total_length is :%d\n", ntohs(ipptr->tot_len));
		printf ("the IP protocol is %d\n", ipptr->protocol);
		addr.s_addr = ipptr->daddr;
		printf ("Destination IP: %s\n", inet_ntoa(addr));    
		addr.s_addr = ipptr->saddr;
		printf ("Source IP: %s\n", inet_ntoa(addr));

		tcpptr = (struct tcphdr *) (packet + 14 + ipptr->ihl*4);
		printf ("Destination port : %d\n", ntohs(tcpptr->dest));
		printf ("Source port : %d\n", ntohs(tcpptr->source));
		printf ("the seq of packet is %u\n", ntohl(tcpptr->seq));
	}
	return 0;
} catch (const runtime_error &e) {
	printf("%s\n", e.what());
	return 1;
}
