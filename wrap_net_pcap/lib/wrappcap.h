#ifndef	WRAPPCAP_H
#define	WRAPPCAP_H

#include <pcap.h>

/**
 * 获得指定网络设备的网络号和掩码:
 * netp参数和maskp参数都是bpf_u_int32指针.
 */
void Pcap_lookupnet(const char *device, bpf_u_int32 *netaddr, bpf_u_int32 *netmask);

/**
 * 获得用于捕获网络数据包的数据包捕获描述字:
 * device参数为指定打开的网络设备名,
 * snaplen参数定义捕获数据的最大字节数,
 * promisc指定是否将网络接口置于混杂模式,
 * to_ms参数指定超时时间（毫秒）.
 */
pcap_t *Pcap_open_live(const char *device, int snaplen, int promisc, int to_ms);

/**
 * 打开以前保存捕获数据包的文件, 用于读取:
 * fname参数指定打开的文件名,
 * 该文件中的数据格式与tcpdump和tcpslice兼容, 
 * "-"为标准输入
 */
pcap_t *Pcap_open_offline(const char *fname);

/**
 * 将rule参数指定的字符串编译到过滤程序中:
 * netmask参数指定本地网络的网络掩码.
 */
void Pcap_setfilter(pcap_t *p, const char *rule, int netmask);

#endif
