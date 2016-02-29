# Makefile

RM = rm -f
CXX = g++
CFLAGS = -Wall -g -std=c++11
INCLUDE = -I../include
LDFLAGS = 
LDPATH = 

PROGS =	time_sort test_multiple_merge test_multiple_merge_opt \
	test_outer_sort test_outer_sort_opt time_sort_uint8

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o *.txt
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CFLAGS) $(INCLUDE)

time_sort:	time_sort.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

test_multiple_merge:	test_multiple_merge.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

test_multiple_merge_opt:	test_multiple_merge_opt.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

test_outer_sort:	test_outer_sort.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

test_outer_sort_opt:	test_outer_sort_opt.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

time_sort_uint8:	time_sort_uint8.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

