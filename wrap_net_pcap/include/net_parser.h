#ifndef NET_PARSER_H
#define NET_PARSER_H

#include "net_protocol_info.h"
#include <stdint.h>
#include <string>

// 网络报文解析器
class Net_parser {
	Net_protocol_info m_info;
	std::string m_errmsg;

public:
	// 解析报文:
	// 如果解析成功, 返回true, 
	// 否则返回false, 并把信息记录在error_message?
	bool parse_packet(Net_protocol_info *info, const uint8_t *packet, int pktlen);

	// 解析报文:
	// 如果解析成功, 返回指向Net_protocol_info的指针, 
	// 否则返回NULL, 并把信息记录在error_message?
	Net_protocol_info *parse_packet(const uint8_t *packet, int pktlen)
	{
		return (parse_packet(&m_info, packet, pktlen) ? &m_info : 0);
	}

	// 返回详细错误信息
	const std::string &error_message() const { return m_errmsg; }

public:
	// 重置info
	static void reset(Net_protocol_info *info);
};

#endif
