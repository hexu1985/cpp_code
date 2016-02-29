# Makefile

RM = rm -f
CXX = g++

ifdef slience
QUIET = @
endif

std = c++98

CXXFLAGS = -Wall -g -DNDEBUG -std=$(std)
INCLUDE = -I../type_traits -I../memory -I../key_words -I../functional
LDFLAGS = 
LDPATH = 

PROGS = constructors assign_operator begin_end rbegin_rend empty size max_size \
	front back assign push_front pop_front push_back pop_back insert erase \
	swap resize clear splice remove remove_if unique merge sort reverse \
	get_allocator 

PROGS11 = constructors11 assign_operator11 cbegin_cend crbegin_crend \
	emplace_front emplace_back emplace comparisons11 global_swap11 \
	assign11 push_front11 pop_front11 swap11 resize11 clear11 remove11 \
	remove_if11 unique11 merge11 sort11 reverse11 \


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

$(PROGS): %: %.cpp $(RELYDIR)
	$(QUIET) $(CXX) -o $@ $< $(CXXFLAGS) $(INCLUDE) $(LDPATH) $(LDFLAGS)

