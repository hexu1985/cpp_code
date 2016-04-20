#ifndef	HTTP_AGENT_H
#define	HTTP_AGENT_H

#include "net_packet.h"
#include "net_processor.h"
#include "net_tcp_faker.h"
#include <map>
#include <string>
#include <boost/smart_ptr.hpp>

class Http_agent: public Net_processor<Net_packet> {
private:
	struct Client_id {
		uint32_t ip;	// network bytes order
		uint16_t port;	// network bytes order
	};

	friend bool operator <(const Client_id &a, const Client_id &b)
	{
		return (a.ip < b.ip) || ((a.ip == b.ip) && a.port < b.port);
	}

	struct Http_resp {
		uint32_t beg_seq;						// http_resp begin seqno
		boost::shared_ptr<std::string> pbuf;	// resp data
	};

	typedef std::map<Client_id, Http_resp> Http_resp_map;

private:
	int m_id;						// processor id
	Net_tcp_faker m_tcp_faker;		// tcp faker
	Http_resp_map m_http_resp_map;	// flows map

public:
	Http_agent(const char *device, int id);

	void process(const Net_packet &pkt);

	void free(Net_task_node<Net_packet> *task);
};

#endif
