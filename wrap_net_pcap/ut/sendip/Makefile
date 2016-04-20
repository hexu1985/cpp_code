
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDES = -I../../lib/
LDFLAGS = -lnet
LDPATH =
VPATH = ../../lib

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: sendip 
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

sendip: sendip.cpp wraplibnet.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)

