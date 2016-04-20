#include "str_util.h"

using namespace std;

string strip(const string &str)
{
    size_t beg = str.find_first_not_of(' ');
    size_t end = str.find_last_not_of(' ');
	if (beg == string::npos || end == string::npos)
		return "";
    return str.substr(beg, end-beg+1);
}

