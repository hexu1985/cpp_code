#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <string>
#include <iostream>
#include <fstream>
#include <boost/thread.hpp>
#include <boost/tuple/tuple.hpp>
#include "net_processor_pool.h"
#include "net_sniffer.h"
#include "net_parser.h"
#include "net_util.h"
#include "str_util.h"
#include "http_cookie.h"
#include "ip2clueid_map.h"

using namespace std;
using namespace boost;

void usage(char *cmdname)
{
	const char *optstr = 
		"[ -i devname/pcapfile ] [ -o output_dir ] "
		"[ -h host_list_file ] [ -c clueip_file ] ";
	printf("usage: %s %s\n", cmdname, optstr);
}

vector<string> load_host_filter_list(const char *file_path);
void reload_ip2clueid_map(Ip2clueid_map &ip2clueid_map);

int main(int argc, char *argv[])
{
	int num_agents = 1;
	string devname; 
	uint16_t port = htons(80);				// 网络字节序
	string output_dir = ".";
	string clueip_file;
	vector<string> host_filter_list;

	if (argc == 1) {
		usage(argv[0]);
		exit(1);
	}

	// 解析输入参数
	int opt;
    while((opt = getopt(argc, argv, ":i:o:h:c:")) != -1) {
        switch(opt) {
        case 'i':
			printf("-i optarg: %s\n", optarg);
			devname = optarg;
			break;
        case 'o':
			printf("-o optarg: %s\n", optarg);
			output_dir = optarg;
			break;
        case 'h':
			printf("-h optarg: %s\n", optarg);
			host_filter_list = load_host_filter_list(optarg);
			break;
        case 'c':
			printf("-c optarg: %s\n", optarg);
			clueip_file = optarg;
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
	
	if (devname.empty()) {
		usage(argv[0]);
		exit(1);
	}

	// 加载ip2clueid map
	Ip2clueid_map ip2clueid_map(clueip_file.c_str());

	// 启动监视clueip_file的线程
	thread clueip_file_watcher(&reload_ip2clueid_map, ref(ip2clueid_map));

	// 创建处理线程池
	Net_processor_pool<Net_packet> processor_pool;
	for (int i = 0; i < num_agents; i++) {
		processor_pool.add_processor(
				make_tuple(new Net_task_queue<Net_packet>, 
					new Http_cookie(output_dir.c_str(), 
						host_filter_list, &ip2clueid_map)
					)
				);
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

	this_thread::sleep_for(chrono::seconds(10));
	// 主线程抓包
	try {
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

		// 解析TCP报首
		if (info.trans_type != Net_protocol_info::TRANS_TCP) {
			continue;
		}
		tcpptr = (struct tcphdr *) (packet + info.trans_off);

		// 过滤目的端口
		if (port != tcpptr->th_dport) {
			continue;
		}

		// 过滤无数据的报文
		if (info.payload_len <= 0) {
			continue;
		}

		// 创建一个包含Net_packet的task node
		node = new node_type;
		net_packet_fill(&node->task, packet, pkthdr, &info);
		processor_pool.push_task(0, node);
	}
	} catch (...) {}

	cout << "hello world!" << endl;
	int c;
	cin >> c; 

	clueip_file_watcher.interrupt();
	clueip_file_watcher.join();
	return 0;
}

// 加载host filter set
vector<string> load_host_filter_list(const char *file_path)
{
	vector<string> host_filter_list;

	ifstream ifile(file_path);
	if (!ifile) {
		cout << "open host filter list file \"" 
			<< file_path << "\" fault" << endl;
		return host_filter_list;
	}

	string str;
	while (getline(ifile, str)) {
		host_filter_list.push_back(strip(str));
		cout << "Host: [" << host_filter_list.back() << "]\n";
	}
	return host_filter_list;
}

void reload_ip2clueid_map(Ip2clueid_map &ip2clueid_map)
{
	while (true) {
		this_thread::sleep_for(chrono::seconds(1));
		ip2clueid_map.reload();
	}
}
