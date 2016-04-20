#include "httpreq.h"
#include "http_parser.h"

#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <string>

using std::vector;
using std::map;
using std::string;

bool httpreq_parse(uint8_t *beg, uint8_t *end, 
		struct Httpreq_header *httpreq_hdr, int *perror)
{
   	uint8_t *mime_beg;

	// 解析request line
	if (!Http_parser::parse_request_line(beg, end, 
				httpreq_hdr->method, httpreq_hdr->uri, httpreq_hdr->version, 
				&mime_beg)) {
#ifndef NDEBUG
		printf("httpreq_parse error: resolve request line fault\n");
#endif
		if (perror) *perror = Http_parser::INVALID_HEADER;
		return false;
	}

	// 解析http mime header
	map<string, string> mime_pairs;
	mime_pairs["Host"] = "";
	mime_pairs["Cookie"] = "";
	if (!Http_parser::parse_mime_header(mime_beg, end, mime_pairs, perror)) {
#ifndef NDEBUG
		printf("httpreq_parse error: resolve request header fault\n");
#endif
		return false;
	}

	httpreq_hdr->host = mime_pairs["Host"];
	httpreq_hdr->cookie = mime_pairs["Cookie"];

	return true;
}

