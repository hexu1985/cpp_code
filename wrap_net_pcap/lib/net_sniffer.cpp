#include "net_sniffer.h"
#include "wrappcap.h"
#include <cassert>
#include <cstring>
#include <string>
#include <stdexcept>

using std::string;
using std::runtime_error;

void Net_sniffer::init()
{
	m_dlt = DLT_NULL;
	m_handle = NULL;
}

Net_sniffer::Net_sniffer()
{
	init();
}

Net_sniffer::Net_sniffer(const char *source)
{
	init();
	open(source);
}

Net_sniffer::~Net_sniffer()
{
	close();
}

void Net_sniffer::open(const char *source)
{
	// 不能重复open
	if (is_open()) {
		throw runtime_error("Net_sniffer::open error: already opened!");
	}

	// 尝试open device
	pcap_t *handle = NULL;
	string errmsg;
	try {
		handle = Pcap_open_live(source, 65536, 1, 0);
		reset(handle);
		return;
	} catch (const runtime_error &e) {
		errmsg += e.what();
	}

	// 尝试open file
	errmsg += '\n';
	handle = NULL;
	try {
		handle = Pcap_open_offline(source);
		reset(handle);
		return;
	} catch (const runtime_error &e) {
		errmsg += e.what();
	}

	throw runtime_error("Net_sniffer::open error:\n"+errmsg); 
}

bool Net_sniffer::is_open() const
{
	return m_handle != NULL;
}

void Net_sniffer::close()
{
	reset();
}

void Net_sniffer::set_filter(const char *rule)
{
	if (!is_open()) {
		throw runtime_error("Net_sniffer::set_filter error: not open!");
	}

	/* Don't care about netmask, it won't be used for this filter */
	int netmask = 0xffffffff;
	Pcap_setfilter(m_handle, rule, netmask);
}

bool Net_sniffer::capture_packet(struct pcap_pkthdr **header, const u_char **packet)
{
	int ret = pcap_next_ex(m_handle, header, packet);
	if (ret > 0) { //ok
		return true;
	} else if (ret == 0) {	//timeout
		return false;
	} else if (ret == -2) { //-2 loop was broken out or EOF
		throw runtime_error("Net_sniffer::next_packet error: "
				"broken out by pcap_breakloop or EOF");
	} else {	//ret < 0 and ret != -2 error  
		throw runtime_error(string("Net_sniffer::next_packet error: ")+
				pcap_geterr(m_handle));
	}
}

void Net_sniffer::next_packet(struct pcap_pkthdr **header, const u_char **packet)
{
	while (!capture_packet(header, packet))
		;
}

Net_sniffer::native_handle_type Net_sniffer::release()
{
	native_handle_type tmp = m_handle;
	reset();
	return tmp;
}

void Net_sniffer::reset(native_handle_type handle)
{
	// close当前handle
	if (m_handle != NULL) {
		pcap_close(m_handle);
	}

	// 设置handle和datalink type
	m_handle = handle;
	m_dlt = (m_handle == NULL) ? DLT_NULL : pcap_datalink(m_handle);
}

