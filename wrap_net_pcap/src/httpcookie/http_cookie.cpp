#include "http_cookie.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <string>
#include <stdexcept>
#include "http_parser.h"
#include "httpreq.h"
#include "net_task_list.h"
#include "gen_file_name.h"
#include "ip2clueid_map.h"

using namespace std;

Http_cookie::Flow_id::Flow_id(struct ip *ipptr, struct tcphdr *tcpptr)
{
	client_ip = ipptr->ip_src.s_addr;
	client_port = tcpptr->th_sport;
	server_ip = ipptr->ip_dst.s_addr;
	server_port = tcpptr->th_dport;
}

Http_cookie::Httpreq_flow::Httpreq_flow(struct tcphdr *tcpptr, 
		char *data, int len)
{
	next_seq = ntohl(tcpptr->seq)+len;
	payload.assign(data, len);
}

Http_cookie::Http_cookie(const char *output_dir,
		const vector<string> &host_filter_list,
		Ip2clueid_map *ip2clueid_map): 
	m_host_filter_set(host_filter_list.begin(), host_filter_list.end()),
	m_output_dir(output_dir), 
	m_ip2clueid_map(ip2clueid_map)
{
}

void Http_cookie::process(const Net_packet &pkt)
{
	assert(pkt.hdr_ip);
	assert(pkt.hdr_tcp);
	assert(pkt.hdr_body);

	// process http get
	int req_payload_len   = pkt.body_len;
	char *req_payload     = (char *) pkt.hdr_body; 

	struct ip *ipptr      = pkt.hdr_ip;
	struct tcphdr *tcpptr = pkt.hdr_tcp;
	Flow_id fid(ipptr, tcpptr);

	Httpreq_header httpreq_hdr;
	int error;

	// check http get
	if (!httpreq_parse((uint8_t *) req_payload, 
			(uint8_t *) req_payload + req_payload_len,
			&httpreq_hdr, &error)) {
		// 不完整的http报头, 缓存
		if (error == Http_parser::UNCOMPLETED_HEADER) {
			m_httpreq_flow_map.insert(
					make_pair(fid, Httpreq_flow(tcpptr, req_payload, req_payload_len)));
			return;
		} 

		// 查找报文是否为某个不完整http报头的一部分
		assert(error == Http_parser::INVALID_HEADER); 
		Httpreq_flow_map::iterator iter = m_httpreq_flow_map.find(fid);
		if (iter == m_httpreq_flow_map.end()) {
			return;
		}
		Httpreq_flow &flow = iter->second;
		uint32_t seq = ntohl(tcpptr->th_seq);
		if (seq != flow.next_seq) {
			return;
		}
		flow.payload.append(req_payload, req_payload_len);	// 追加数据
		flow.next_seq += req_payload_len;	// 更新next seqno
		if (!httpreq_parse((uint8_t *) flow.payload.c_str(), 
				(uint8_t *) flow.payload.c_str() + flow.payload.size(),
				&httpreq_hdr)) {
			return;
		}

		// 拼流结束, 删除缓存
		m_httpreq_flow_map.erase(iter);
	}

#ifndef NDEBUG
	cout << "httpcookie:\n";
	cout << "HTTP version: " << httpreq_hdr.version << '\n';
	cout << "HTTP method: " << httpreq_hdr.method << '\n';
	cout << "HTTP uri: " << httpreq_hdr.uri << '\n';
	cout << "HTTP host: " << httpreq_hdr.host << '\n';
	cout << "HTTP cookie: " << httpreq_hdr.cookie << '\n';
	cout << endl;
#endif

	// 过滤掉没有Host或Cookie的
	if (httpreq_hdr.host.empty() || httpreq_hdr.cookie.empty()) {
		return;
	}

	// 过滤Host
	if (!is_care_host(httpreq_hdr.host)) {
		return;
	}

	// 写入文件
	dump_file(fid, httpreq_hdr);

	return;
}

void Http_cookie::free(Net_task_node<Net_packet> *task)
{
	delete task;
}

void Http_cookie::dump_file(const Flow_id &fid, const Httpreq_header &httpreq)
{
	// 查找clueid
	int clueid = 0;
	if (m_ip2clueid_map != NULL) {
		Ip2clueid_map &ip2clueid_map = *m_ip2clueid_map;
		clueid = ip2clueid_map[fid.client_ip];
	}

	// 构造文件全路径
	string filepath = m_output_dir;
	filepath += '/';
	filepath += gen_file_name();

#ifndef NDEBUG
	cout << "outfile: " << filepath << endl;
#endif

	// 写文件
	ofstream ofile(filepath.c_str());
	if (!ofile) {
		throw runtime_error("open file \""+filepath+"\" for write fault!");
	}

	ofile << "Clueid: " << clueid << '\n'
		<< "Host: " << httpreq.host << '\n'
		<< "Cookie: " << httpreq.cookie << endl;

	ofile.close();
}

bool Http_cookie::is_care_host(const std::string &host)
{
	// 过滤Host
	if (!m_host_filter_set.empty() && 
			m_host_filter_set.find(host) == m_host_filter_set.end()) {
		// no found
		return false;
	}

	return true;
}

