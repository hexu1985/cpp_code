# my makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g 
INCLUDE = 
LDFLAGS = 
LDPATH = 

TARGETS = test_double_linked_list

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	rm -rf $(TARGETS) *.exe *.dSYM

test_double_linked_list: test_double_linked_list.cpp double_linked_list.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) $(LDPATH)

