/* Simple ARP sniffer
 * To compile: gcc arpsniffer.c -o arpsniff -lpcap
 * Run as root!
 * */
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "net_sniffer.h"
#include <stdexcept>

using namespace std;

//ARP Header, (assuming Ethernet+ipv4)
#define ARP_REQUEST 1
#define ARP_REPLY 2
typedef struct arphdr {
	u_int16_t htype; //hardware type
	u_int16_t ptype; //protocol type
	u_char hlen; //hardware address length
	u_char plen; //protocol address length
	u_int16_t oper; //operation code
	u_char sha[6]; //sender hardware address
	u_char spa[4]; //sender ip address
	u_char tha[6]; //target hardware address
	u_char tpa[4]; //target ip address
} arphdr_t;

#define MAXBYTES2CAPTURE 2048
int main(int argc, char *argv[]) try
{
	int i=0;
	struct pcap_pkthdr *pkthdr;
	const unsigned char *packet = NULL;
	arphdr_t *arpheader = NULL;

	if (argc != 2){
		printf("Usage: arpsniffer <interface/pcapfile>\n");
		exit(1);
	}

	Net_sniffer sniffer;
	sniffer.open(argv[1]);
	sniffer.set_filter("arp");

	if (sniffer.datalink_type() != DLT_EN10MB) {
		printf("not support datalink type!");
		exit(1);
	}

	while (1){
		sniffer.next_packet(&pkthdr, &packet);

		arpheader = (struct arphdr *)(packet + 14);
		printf("\n\nReceived Packet Size: %d bytes\n", pkthdr->len);
		printf("Hardware type: %s\n", (ntohs(arpheader->htype) == 1) ?
			"Ethernet" : "Unknown");
		printf("Protocol type: %s\n", (ntohs(arpheader->ptype) == 0x0800) ?
			"Ethernet" : "Unknown");
		printf("Operation: %s\n", (ntohs(arpheader->oper) == ARP_REQUEST) ?
				"ARP Request" : "ARP Reply");
		if (ntohs(arpheader->htype) == 1 && ntohs(arpheader->ptype) == 0x0800) {
			printf("Sender MAC: ");
			for (i=0; i<6; i++) printf("%02x:", arpheader->sha[i]);
			printf("\nSender IP: ");
			for (i=0; i<4; i++) printf("%d.", arpheader->spa[i]);
			printf("\nTarget MAC: ");
			for (i=0; i<6; i++) printf("%02x:", arpheader->tha[i]);
			printf("\nTarget IP: ");
			for (i=0; i<4; i++) printf("%d.", arpheader->tpa[i]);
			printf("\n");
		}
	}
	return 0;
} catch (const runtime_error &e) {
	printf("%s\n", e.what());
	return 1;
}
