# Makefile

RM = rm -f
CXX = g++

ifdef slience
QUIET = @
endif

std = c++98

CXXFLAGS = -Wall -g -DNDEBUG -std=$(std)
INCLUDE = -I../memory -I../algorithm -I../type_traits -I../key_words
LDFLAGS =
LDPATH = 

PROGS = constructors assign_operator begin end rbegin_rend size \
	max_size_capacity resize empty reserve shrink_to_fit access_operator at \
	front back linearize assign push_back push_front pop_back pop_front \
	insert erase swap clear get_allocator comparisons global_swap 

PROGS11 = constructors11 assign_operator11 assign11 insert11 cbegin_cend11 \
	crbegin_crend11 emplace emplace_front emplace_back 

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

