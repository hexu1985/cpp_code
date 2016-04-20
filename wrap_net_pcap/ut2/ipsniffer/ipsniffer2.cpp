/* Simple ARP sniffer
 * To compile: gcc ipsniffer.c -o ipsniffer -lpcap
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
#include "net_sniffer.h"
#include <stdexcept>

using namespace std;

#define MAXBYTES2CAPTURE 2048
int main(int argc, char *argv[]) try
{
	struct pcap_pkthdr *pkthdr;
	const unsigned char *packet = NULL;
	struct ip *ipptr = NULL;

	if (argc != 2){
		printf("Usage: ipsniffer <interface>\n");
		exit(1);
	}

	Net_sniffer sniffer;
	sniffer.open(argv[1]);
	sniffer.set_filter("ip");

	if (sniffer.datalink_type() != DLT_EN10MB) {
		printf("not support datalink type!");
		exit(1);
	}

	while (1){
		sniffer.next_packet(&pkthdr, &packet);

		ipptr = (struct ip *)(packet + 14);
		printf("\n\nReceived Packet Size: %d bytes\n", pkthdr->len);
		printf("\n\nthe IP packets version: %d\n", ipptr->ip_v); 
		printf ("the IP packets total_length is :%d\n", ntohs(ipptr->ip_len));
		printf ("the IP protocol is %d\n", ipptr->ip_p);
		printf ("Destination IP: %s\n", inet_ntoa(ipptr->ip_dst));    
		printf ("Source IP: %s\n", inet_ntoa(ipptr->ip_src));
	}
	return 0;
} catch (const runtime_error &e) {
	printf("%s\n", e.what());
	return 1;
}
