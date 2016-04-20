#include "wrappcap.h"
#include <cassert>
#include <string>
#include <stdexcept>

using std::string;
using std::runtime_error;

void Pcap_lookupnet(const char *device, bpf_u_int32 *netaddr, bpf_u_int32 *netmask)
{
	char errbuf[PCAP_ERRBUF_SIZE];
	if (pcap_lookupnet(device, netaddr, netmask, errbuf) < 0) {
		throw runtime_error("Pcap_lookupnet error: "+string(errbuf));
	}
}

pcap_t *Pcap_open_live(const char *device, int snaplen, int promisc, int to_ms)
{
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *p = pcap_open_live(device, snaplen, promisc, to_ms, errbuf);
	if (p == NULL) {
		throw runtime_error("Pcap_open_live error: "+string(errbuf));
	}
	return p;
}

pcap_t *Pcap_open_offline(const char *fname)
{
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *p = pcap_open_offline(fname, errbuf);
	if (p == NULL) {
		throw runtime_error("Pcap_open_offline error: "+string(errbuf));
	}
	return p;
}

void Pcap_setfilter(pcap_t *p, const char *rule, int netmask)
{
	assert(p);

	/* Don't care about netmask, it won't be used for this filter */
	struct bpf_program filter;
	int ret;

	// compile the filter 
	if (pcap_compile(p, &filter, (char *) rule, 1, netmask) < 0) {
		throw runtime_error("Pcap_setfilter error: "+string(pcap_geterr(p)));
	}

	// set the filter
	ret = pcap_setfilter(p, &filter);
	pcap_freecode(&filter);
	if (ret < 0) {
		throw runtime_error("Pcap_setfilter error: "+string(pcap_geterr(p)));
	}
}
