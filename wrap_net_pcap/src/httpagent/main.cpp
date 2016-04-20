#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <string>
#include <iostream>
#include <boost/tuple/tuple.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/functional/hash.hpp>
#include "net_processor_pool.h"
#include "net_sniffer.h"
#include "net_parser.h"
#include "net_util.h"
#include "http_agent.h"

using std::cin;
using std::cout;
using std::cerr;
using std::string;
using std::endl;
using boost::make_tuple;
using boost::lexical_cast;
using boost::hash_combine;

namespace {

void usage(char *cmdname)
{
	const char *optstr = 
		"[ -i devname ] [ -a addr ] [ -p port ] [ -n threads ]";
	printf("usage: %s %s\n", cmdname, optstr);
}

size_t calculate_hash_code(struct ip *ipptr, struct tcphdr *tcpptr)
{
	size_t seed = 0;
	hash_combine(seed, ipptr->ip_src.s_addr);
	hash_combine(seed, tcpptr->th_sport);
	return seed;
}

}

int main(int argc, char *argv[])
{
	int num_agents = 0;
	string devname; 
	in_addr_t addr = INADDR_NONE;	// 网络字节序
	uint16_t port = 0;				// 网络字节序

	if (argc == 1) {
		usage(argv[0]);
		exit(1);
	}

	// 解析输入参数
	int opt;
    while((opt = getopt(argc, argv, ":i:a:p:n:")) != -1) {
        switch(opt) {
        case 'i':
			printf("-i optarg: %s\n", optarg);
			devname = optarg;
			break;
        case 'a':
			printf("-a optarg: %s\n", optarg);
			addr = inet_addr(optarg);
			if (addr == INADDR_NONE) {
				cerr << "invalid ip " << optarg << '\n';
				exit(1);
			}
			break;
        case 'p':
			printf("-p optarg: %s\n", optarg);
			port = lexical_cast<uint16_t>(optarg);
			port = htons(port);
            break;
        case 'n':
			printf("-n optarg: %s\n", optarg);
			num_agents = lexical_cast<int>(optarg);
            break;
        case ':':
            printf("option needs a value\n");
			usage(argv[0]);
			exit(1);
            break;
        case '?':
            printf("unknown option: %c\n", optopt);
			usage(argv[0]);
			exit(1);
            break;
        }
    }

	// 创建处理线程池
	Net_processor_pool<Net_packet> processor_pool;
	for (int i = 0; i < num_agents; i++) {
		processor_pool.add_processor(
				make_tuple(new Net_task_queue<Net_packet>, 
					new Http_agent(devname.c_str(), i)));
	}

	// 创建sniffer
	Net_sniffer sniffer;
	sniffer.open(devname.c_str());

	if (sniffer.datalink_type() != DLT_EN10MB) {
		printf("not support datalink type!");
		exit(1);
	}

	// 创建parser
	Net_parser parser;
	Net_protocol_info info;

	struct pcap_pkthdr *pkthdr;
	const unsigned char *packet = NULL;
	struct ip *ipptr = NULL;
	struct tcphdr *tcpptr = NULL;
	typedef Net_processor_pool<Net_packet>::node_type node_type; 
	node_type *node = NULL;

	// 主线程抓包
	while (true) {
		sniffer.next_packet(&pkthdr, &packet);

		if (net_packet_is_truncate(pkthdr)) {
#ifndef NDEBUG
			cerr << "packet is truncate! "
				<< "caplen: " << pkthdr->caplen
				<< ", len: " << pkthdr->len << ".\n"; 
#endif
			continue;
		}

		if (!parser.parse_packet(&info, packet, pkthdr->caplen)) {
#ifndef NDEBUG
			cerr << parser.error_message() << '\n';
#endif
			continue;
		}

		// 解析IP报首
		if (info.inet_type != Net_protocol_info::INET_IPV4) {
			continue;
		}
		ipptr = (struct ip *)(packet + info.inet_off);

		// 过滤目的IP
		if (ipptr->ip_dst.s_addr != addr) {
			continue;
		}

		// 解析TCP报首
		if (info.trans_type != Net_protocol_info::TRANS_TCP) {
			continue;
		}
		tcpptr = (struct tcphdr *) (packet + info.trans_off);

		// 过滤目的端口
		if (port != tcpptr->th_dport) {
			continue;
		}

		int index_agent = calculate_hash_code(ipptr, tcpptr) % num_agents;

		// 创建一个包含Net_packet的task node
		node = new node_type;
		net_packet_fill(&node->task, packet, pkthdr, &info);
		processor_pool.push_task(index_agent, node);
	}

	cout << "hello world!" << endl;
	int c;
	cin >> c; 
	return 0;
}
