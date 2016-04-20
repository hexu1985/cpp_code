#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include "gen_file_name.h"
#include <string.h>
#include <errno.h>
#include <stdexcept>
#include <string>
#include <sstream>

using namespace std;

namespace {

void Gettimeofday(struct timeval *tp)
{
	if (gettimeofday(tp, NULL) < 0) {
		throw runtime_error("gettimeofday error: "+string(strerror(errno)));
	}
}

}

std::string gen_file_name()
{
	// 获取当前时间
	struct timeval now;
	Gettimeofday(&now);

	// 显示时间
	struct tm *timeinfo;
	char buffer[80];
	timeinfo = localtime(&now.tv_sec);

	strftime(buffer, 80, "%Y%m%d%H%M%S", timeinfo);
	ostringstream os;
	os << buffer << '.' << now.tv_usec;

	return os.str();
}

