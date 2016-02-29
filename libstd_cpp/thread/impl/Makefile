# Makefile

AR = ar r
RM = rm -f
MV = mv
CXX = g++

ifdef slience
QUIET = @
endif

std = c++98

CXXFLAGS = -Wall -g -DNDEBUG -std=$(std)
INCLUDE += -I../../functional -I../../system_error -I../../type_traits \
	-I../../chrono -I../../common -I../../limits -I../../ratio \
	-I../../key_words
LDFLAGS = 
LDPATH = 

RELYDIR := ../system_error
OBJS = call_once.o notify_all_at_thread_exit.o
LIB = libthread.a

.PHONY: all
all: $(LIB)
	@echo "build OK!"

.PHONY: clean
clean:
	$(QUIET) $(RM) $(OBJS) $(LIB) *.o *.exe *.obj 
	@echo "clean OK!"

$(OBJS): %.o: %.cpp
	$(QUIET) $(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

$(LIB): $(OBJS)
	$(QUIET) $(AR) $@ $?

