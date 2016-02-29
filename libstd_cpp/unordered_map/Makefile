# Makefile

RM = rm -f
CXX = g++

ifdef slience
QUIET = @
endif

std = c++98

CXXFLAGS = -Wall -g -std=$(std) -DNDEBUG 
INCLUDE = -I../type_traits -I../memory -I../key_words -I../functional \
	-I../forward_list/impl 
LDFLAGS = 
LDPATH = 

PROGS = access_operator begin_end empty size find insert erase clear rehash \
	load_factor hash_function key_eq limits comparisions equal_range swap \
	assign_operator 
PROGS11 = constructors11 comparisions11 assign_operator11 at11 count11 \
	bucket_size11 bucket11 emplace cbegin_cend swap11 insert11 \
	bucket_count11 bucket_size11_with_shrink bucket_count11_with_shrink \
	empty11 size11 erase11 find11

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

