# my makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g 
INCLUDE = 
LDFLAGS = 
LDPATH = 

TARGETS = test_binary_search_tree

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	rm -rf $(TARGETS) *.exe *.dSYM

test_binary_search_tree: test_binary_search_tree.cpp binary_search_tree.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) $(LDPATH)

