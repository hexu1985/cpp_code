#ifndef	IP2CLUEID_MAP_H 
#define	IP2CLUEID_MAP_H 

#include <stdint.h>
#include <time.h>
#include <string>
#include <boost/unordered_map.hpp>
#include <boost/thread/mutex.hpp>

class Ip2clueid_map {
	boost::unordered_map<uint32_t, int> m_ip2clueid_map;	// ip to clueid
	boost::mutex m_map_mtx;	// mutex for ip to cluied map
	time_t m_last_mtime;	// last modify time
	std::string m_clueip_file_path;	// clueip file

public:
	// 构造Ip2cluied map
	Ip2clueid_map(const char *file_path);

	// 通过ip查找clueid, 0为海量
	int operator [](uint32_t ip);

	// 重新加载map
	void reload();
};

#endif
