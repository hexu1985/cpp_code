# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
INCLUDE = 
LDFLAGS = -lpthread
LDPATH = 

PROGS =	test_local test_global test_pointer mt_test_local mt_test_global mt_test_pointer
.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

test_local: test.o singleton.o local_static_instance.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

test_global: test.o singleton.o global_static_instance.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

test_pointer: test.o singleton.o pointer_instance.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

mt_test_local: mt_test.o singleton.o local_static_instance.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

mt_test_global: mt_test.o singleton.o global_static_instance.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

mt_test_pointer: mt_test.o singleton.o pointer_instance.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

