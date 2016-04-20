
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -DNDEBUG
INCLUDES = -I../../include
LDFLAGS = -lnet -lpcap -lboost_thread -lboost_system
LDPATH =
VPATH = ../../lib

SOURCES = $(shell ls *.cpp)
PROGS = httpagent
LIB_SOURCES = dlist_base.cpp net_sniffer.cpp wrappcap.cpp net_parser.cpp \
			  net_protocol_info.cpp net_util.cpp net_packet.cpp \
			  net_tcp_faker.cpp net_faker_base.cpp wraplibnet.cpp \
			  http_parser.cpp str_util.cpp

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

$(PROGS): $(SOURCES) $(LIB_SOURCES)
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
