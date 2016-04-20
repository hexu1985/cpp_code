#ifndef WGET_LOCAL_H
#define WGET_LOCAL_H

#include <stdint.h>
#include <boost/shared_ptr.hpp>
#include <string>

boost::shared_ptr<std::string> wget_local(const char *httpget, int httpget_len);

#endif
