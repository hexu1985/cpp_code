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

PROGS = constructors assign_operator begin_end empty max_size assign \
	push_front pop_front swap resize clear remove remove_if unique merge \
	sort reverse get_allocator
PROGS11 = constructors11 assign_operator11 before_begin11 begin11 end11 \
	cbefore_begin11 cbegin_cend empty11 front11 assign11 emplace_front \
	push_front11 pop_front11 emplace_after insert_after11 erase_after11 \
	swap11 resize11 clear11 splice_after11 remove11 remove_if11 unique11 \
	merge11 sort11 reverse11 comparisons11 global_swap11

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

