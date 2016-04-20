#ifndef NET_SNIFFER_H
#define NET_SNIFFER_H

#include <pcap.h>

// 网络嗅探器
// 抓取网卡上的报文,
// 或者从pcap文件读取报文
class Net_sniffer {
	int m_dlt;					// datalink type
	pcap_t *m_handle;			// libpcap handle

public:
	Net_sniffer();
	Net_sniffer(const char *source);

	~Net_sniffer();

	// 打开嗅探器, source为设备名或是pcap文件路径
	void open(const char *source);

	// 嗅探器是否打开
	bool is_open() const;

	// 获取数据链路类型
	int datalink_type() const { return m_dlt; }

	// 抓取下一个报文:
	// 非阻塞方式
	bool capture_packet(struct pcap_pkthdr **header, const u_char **packet);

	// 抓取下一个报文:
	// 阻塞方式
	void next_packet(struct pcap_pkthdr **header, const u_char **packet);

	// 关闭嗅探器
	void close();

	// 设置过滤器
	void set_filter(const char *rule);

public:
	// 获取native handle
	typedef pcap_t *native_handle_type;
	native_handle_type native_handle() { return m_handle; }

	// 释放native handle
	native_handle_type release();

	// reset native handle
	void reset(native_handle_type handle = NULL);

private:
	// 初始化函数
	void init();

private:
	// delete operator
	Net_sniffer(const Net_sniffer &);
	Net_sniffer &operator =(const Net_sniffer &);
};

#endif
