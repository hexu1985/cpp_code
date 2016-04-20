#ifndef	NET_PROTOCOL_INFO_H
#define	NET_PROTOCOL_INFO_H

// 网络报文解析信息
struct Net_protocol_info {
	enum {OFFSET_INVALID = -1};
	int ether_off;			//以太网报首偏移量
	int vlan_off;			//vlan头开始偏移量
	int vlan_num;			//vlan头层数
	int pppoe_off;			//pppoe报首偏移量
	enum Inet_type { INET_IPV4, INET_IPV6, INET_INVALID } inet_type;
	int inet_off;			//网络层报首偏移量
	enum Trans_type { TRANS_TCP, TRANS_UDP, TRANS_INVALID } trans_type;
	int trans_off;			//传输层报首
	int	payload_off;		//应用层协议偏移量
	int	payload_len;		//应用层协议数据长度
};

// 初始化
void net_protocol_info_init(struct Net_protocol_info *info);

#endif
