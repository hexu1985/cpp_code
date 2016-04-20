
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDES = -I../../include
LDFLAGS = -lpcap
LDPATH =
VPATH = ../../lib

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)
LIB_SOURCES = wrappcap.cpp net_sniffer.cpp

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

%: %.cpp $(LIB_SOURCES)
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
