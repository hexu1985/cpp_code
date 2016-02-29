# Makefile

RM = rm -f
CXX = g++

ifdef slience
QUIET = @
endif

CXXFLAGS = -Wall -g -std=c++11
INCLUDE = -I../vector
LDFLAGS = 
LDPATH = 

PROGS = huffman_encode huffman_decode

ifeq ($(std), c++11)
PROGS += $(PROGS11)
endif

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

.PHONY: clean
clean:
	$(QUIET) $(RM) $(PROGS) $(PROGS11) *.o *.obj *.exe
	@echo "clean OK!"

huffman_encode: huffman_encode.cpp huffman_util.cpp
	$(QUIET) $(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE) $(LDPATH) $(LDFLAGS)

huffman_decode: huffman_decode.cpp huffman_util.cpp
	$(QUIET) $(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE) $(LDPATH) $(LDFLAGS)

