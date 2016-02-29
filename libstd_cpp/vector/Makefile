# Makefile

RM = rm -f
CXX = g++

ifdef slience
QUIET = @
endif

std = c++98

CXXFLAGS = -Wall -g -std=$(std) #-DNDEBUG 
INCLUDE = -I../memory -I../algorithm -I../type_traits -I../key_words
LDFLAGS =
LDPATH = 

PROGS =	constructors assign_operator begin_end rbegin_rend size \
	max_size_capacity resize empty reserve shrink_to_fit access_operator at \
	front back data assign push_back pop_back insert erase swap clear \
	get_allocator comparisons global_swap sizeof

PROGS11 = constructors11 assign_operator11 insert11 assign11 cbegin_cend11 \
	crbegin_crend11 emplace emplace_back custom_allocator

ifeq ($(std), c++11)
PROGS += $(PROGS11)
endif

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	$(QUIET) $(RM) $(PROGS) $(PROGS11) *.o *.obj *.exe
	@echo "clean OK!"

$(PROGS):%:%.cpp
	$(QUIET) $(CXX) -o $@ $< $(CXXFLAGS) $(INCLUDE)

