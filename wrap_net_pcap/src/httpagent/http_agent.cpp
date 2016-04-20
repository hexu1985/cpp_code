#include "http_agent.h"
#include <iostream>
#include <algorithm>
#include "httpreq.h"
#include "wget_local.h"
#include "net_task_list.h"

using std::cout;
using std::endl;
using std::min;

namespace {

uint32_t get_data_off(struct tcphdr *tcpptr, uint32_t beg_seq)
{
	uint32_t next_seq = ntohl(tcpptr->th_ack);
	return next_seq - beg_seq;
}

}

Http_agent::Http_agent(const char *device, int id): 
	m_id(id), m_tcp_faker(device)
{
}

void Http_agent::process(const Net_packet &pkt)
{
	assert(pkt.hdr_ether);
	assert(pkt.hdr_ip);
	assert(pkt.hdr_tcp);

	Http_resp_map::iterator iter;
	struct ether_header *eptr   = pkt.hdr_ether;
	struct Net_vlan_hdr *vlan   = pkt.hdr_vlan;
	int vlan_num                = pkt.vlan_num;
	struct Net_pppoe_hdr *pppoe = pkt.hdr_pppoe;
	struct ip *ipptr            = pkt.hdr_ip;
	struct tcphdr *tcpptr       = pkt.hdr_tcp;

	uint8_t tcp_flags = tcpptr->th_flags;
	// process syn connect handle
	if ((tcp_flags & TH_SYN) && !(tcp_flags & TH_ACK)) {
		m_tcp_faker.send_tcp_syn_ack(tcpptr, ipptr, pppoe, vlan, vlan_num, eptr);
		return;
	}

	// get client ip and port
	Client_id client_id;
	client_id.ip = ipptr->ip_src.s_addr;
	client_id.port = tcpptr->th_sport;

	// process fin disconnect handle
	if (tcp_flags & TH_FIN) {
#ifndef NDEBUG
		cout << "httpagent[" << m_id << "]:\n";
		cout << "tcp fin, map size: " << m_http_resp_map.size() << "\n";
#endif
		m_tcp_faker.send_tcp_fin_ack(tcpptr, ipptr, pppoe, vlan, vlan_num, eptr);
		m_http_resp_map.erase(client_id);
		return;
	}

	// process rst
	if (tcp_flags & TH_RST) {
#ifndef NDEBUG
		cout << "httpagent[" << m_id << "]:\n";
		cout << "tcp rst, map size: " << m_http_resp_map.size() << "\n";
#endif
		m_http_resp_map.erase(client_id);
		return;
	}

	if (!(tcp_flags & TH_ACK))
		return;

	// process http get
	int req_payload_len = pkt.body_len;
	char *req_payload = (char *) pkt.hdr_body; 
	Http_resp http_resp;
	if (req_payload_len != 0) {
		// process psh 
		m_tcp_faker.send_tcp_ack(tcpptr, ipptr, pppoe, vlan, vlan_num, eptr);

#ifndef NDEBUG
		Httpreq_header httpreq_hdr;
		// check http get
		if (!httpreq_parse((uint8_t *) req_payload, 
					(uint8_t *) req_payload + req_payload_len,
					&httpreq_hdr)) {
			return;
		}

		cout << "httpagent[" << m_id << "]:\n";
		cout << "HTTP version: " << httpreq_hdr.version << '\n';
		cout << "HTTP method: " << httpreq_hdr.method << '\n';
		cout << "HTTP uri: " << httpreq_hdr.uri << '\n';
		cout << "HTTP host: " << httpreq_hdr.host << '\n';
		cout << "HTTP user_agent: " << httpreq_hdr.user_agent << '\n';
		cout << endl;
#endif

		// check repeat request
		iter = m_http_resp_map.find(client_id);

		if (iter == m_http_resp_map.end() ||
			iter->second.beg_seq != ntohl(tcpptr->th_ack)) {
			// wget from localhost http server
			http_resp.beg_seq = ntohl(tcpptr->th_ack);
			http_resp.pbuf = wget_local(req_payload, req_payload_len);
			m_http_resp_map[client_id] = http_resp;
#ifndef NDEBUG
			cout << "httpagent[" << m_id << "]:\n";
			cout << "read size: " << http_resp.pbuf->size() << endl;
#endif
		}
		m_tcp_faker.send_tcp_data(http_resp.pbuf->data(), 
				min<int>(http_resp.pbuf->size(), Net_tcp_faker::MAX_SEND_LEN),
				tcpptr, ipptr, pppoe, vlan, vlan_num, eptr);
		return;
	}

	// process ack
	iter = m_http_resp_map.find(client_id);
	if (iter == m_http_resp_map.end()) {
#ifndef NDEBUG
		cout << "httpagent[" << m_id << "]:\n";
		cout << "invalid flows" << endl;
#endif
		return;
	}

	http_resp = iter->second;
	uint32_t data_off = get_data_off(tcpptr, http_resp.beg_seq);
	if (data_off > http_resp.pbuf->size()) {
#ifndef NDEBUG
		cout << "httpagent[" << m_id << "]:\n";
		cout << "data_off: " << data_off << endl;
		cout << "http_resp.pbuf->size(): " << http_resp.pbuf->size() << endl;
		cout << "out of range\n" << endl;
#endif
		m_tcp_faker.send_tcp_rst(tcpptr, ipptr, pppoe, vlan, vlan_num, eptr);
		m_http_resp_map.erase(iter);
		return;
	}
	m_tcp_faker.send_tcp_data(http_resp.pbuf->data() + data_off, 
			min<int>(http_resp.pbuf->size()-data_off, 
				2*Net_tcp_faker::MAX_SEND_LEN),
			tcpptr, ipptr, pppoe, vlan, vlan_num, eptr);

	return;
}

void Http_agent::free(Net_task_node<Net_packet> *task)
{
	delete task;
}
