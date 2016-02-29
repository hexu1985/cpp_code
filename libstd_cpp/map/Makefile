# Makefile

RM = rm -f
CXX = g++

ifdef slience
QUIET = @
endif

std = c++98

CXXFLAGS = -Wall -g -DNDEBUG -std=$(std)
INCLUDE = -I../type_traits -I../memory -I../key_words -I../functional \
	-I../forward_list/impl 
LDFLAGS = 
LDPATH = 

PROGS = access_operator constructors begin_end insert rbegin_rend empty erase \
	assign_operator swap clear key_comp value_comp find count \
	lower_bound_upper_bound equal_range get_allocator
PROGS11 = insert11 cbegin_cend crbegin_crend empty11 size11 assign_operator11 \
	at11 emplace emplace_hint find11

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

$(PROGS): %: %.cpp 
	$(QUIET) $(CXX) -o $@ $< $(CXXFLAGS) $(INCLUDE) $(LDPATH) $(LDFLAGS)

