#include "net_protocol_info.h"

void net_protocol_info_init(struct Net_protocol_info *info)
{
	info->ether_off = -1;			//以太网报首偏移量
	info->vlan_off = -1;			//vlan头开始偏移量
	info->vlan_num = 0;				//vlan头层数
	info->pppoe_off = -1;			//pppoe报首偏移量
	info->inet_type = Net_protocol_info::INET_INVALID;
	info->inet_off = -1;			//网络层报首偏移量
	info->trans_type = Net_protocol_info::TRANS_INVALID;
	info->trans_off = -1;			//传输层报首
	info->payload_off = -1;			//应用层协议偏移量
	info->payload_len = 0;			//应用层协议数据长度
}


