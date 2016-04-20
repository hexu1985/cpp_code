#ifndef	HTTP_COOKIE_H
#define	HTTP_COOKIE_H

#include "net_packet.h"
#include "net_processor.h"
#include <map>
#include <vector>
#include <string>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/functional/hash.hpp>

struct ip;
struct tcphdr;
struct Httpreq_header;
class Ip2clueid_map;

class Http_cookie: public Net_processor<Net_packet> {
private:
	struct Flow_id {
		uint32_t client_ip;
		uint16_t client_port;
		uint32_t server_ip;
		uint16_t server_port;

		Flow_id(struct ip *ipptr, struct tcphdr *tcpptr);
	};

	friend bool operator ==(const Flow_id &a, const Flow_id &b)
	{
		return a.client_ip == b.client_ip &&
			a.client_port == b.client_port && 
			a.server_ip == b.server_ip &&
			a.server_port == b.server_port;
	}

	friend size_t hash_value(const Flow_id &fid)
	{
		size_t seed = 0;
		boost::hash_combine(seed, fid.client_ip);
		boost::hash_combine(seed, fid.client_port);
		boost::hash_combine(seed, fid.server_ip);
		boost::hash_combine(seed, fid.server_port);
		return seed;
	}

	struct Httpreq_flow {
		uint32_t next_seq;			// http_req next packet seqno
		std::string payload;		// http_req data

		Httpreq_flow(struct tcphdr *tcpptr, char *data, int len); 
	};

	typedef boost::unordered_map<Flow_id, Httpreq_flow> Httpreq_flow_map;
	typedef boost::unordered_set<std::string> Host_filter_set;

	Httpreq_flow_map m_httpreq_flow_map;	// 流表
	Host_filter_set m_host_filter_set;		// Host过滤表, 表为空时失效
	const std::string m_output_dir;			// 文件输出路径
	Ip2clueid_map *m_ip2clueid_map;			// ip to clueid map

	// 将信息写入文件
	void dump_file(const Flow_id &fid, const Httpreq_header &httpreq);

	// 过滤host
	bool is_care_host(const std::string &host);

public:
	Http_cookie(const char *output_dir = ".",
			const std::vector<std::string> &host_filter_list = std::vector<std::string>(),
			Ip2clueid_map *ip2clueid_map = NULL);

	void process(const Net_packet &pkt);

	void free(Net_task_node<Net_packet> *task);
};

#endif
