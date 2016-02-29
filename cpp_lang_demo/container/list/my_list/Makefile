
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
INCLUDES = -I./lib
LDFLAGS = -lboost_thread -lboost_system
LDPATH =
VPATH = ./lib

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)
LIB_SOURCES = dlist_base.cpp

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

%: %.cpp $(LIB_SOURCES)
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
