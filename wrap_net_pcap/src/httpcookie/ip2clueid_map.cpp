#include "ip2clueid_map.h"
#include <sys/stat.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <boost/thread/locks.hpp>

using namespace std;
using namespace boost;

namespace {

void load_ip2clueid_map(const char *file_path, 
		unordered_map<uint32_t, int> &ip2clueid_map)
{
	ip2clueid_map.clear();

	ifstream ifile(file_path);
	if (!ifile) {
		throw runtime_error("open file \""+string(file_path)+
				"\" fault for load ip2clueid map");
	}

	string line;
	unsigned int ip;
	unsigned int clueid;
	while (getline(ifile, line)) {
		sscanf(line.c_str(), "%x %x", &ip, &clueid);
		ip = htonl(ip);
		clueid = ntohs(short(clueid));

#ifndef	NDEBUG
		in_addr addr;
		addr.s_addr = ip;
		cout << "ip: " << inet_ntoa(addr) << " clueid: " << clueid << endl;
#endif
		ip2clueid_map[ip] = (int) clueid;
	}
}

}

Ip2clueid_map::Ip2clueid_map(const char *file_path): m_last_mtime(0),
	m_clueip_file_path(file_path)
{
	reload();
}

int Ip2clueid_map::operator [](uint32_t ip) 
{
	lock_guard<mutex> lck(m_map_mtx);
	unordered_map<uint32_t, int>::iterator iter;
	iter = m_ip2clueid_map.find(ip);
	if (iter == m_ip2clueid_map.end())
		return 0;
	else
		return iter->second;
}

void Ip2clueid_map::reload()
{
	struct stat buf;
	if (stat(m_clueip_file_path.c_str(), &buf) < 0) {
		if (errno == ENOENT) {
			return;
		}
		throw runtime_error("stat error for \""+m_clueip_file_path+"\": "+
				string(strerror(errno)));
	}

	// 文件有更新
	if (buf.st_mtime > m_last_mtime) {
		m_last_mtime = buf.st_mtime;
		unordered_map<uint32_t, int> ip2clueid_map;
		load_ip2clueid_map(m_clueip_file_path.c_str(), ip2clueid_map);

		// 交换map
		lock_guard<mutex> lck(m_map_mtx);
		m_ip2clueid_map.swap(ip2clueid_map);
	}
}

