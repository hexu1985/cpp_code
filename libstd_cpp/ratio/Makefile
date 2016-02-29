# Makefile

RM = rm -f
CXX = g++

ifdef slience
QUIET = @
endif

std = c++98

CXXFLAGS = -Wall -g -DNDEBUG -std=$(std)
INCLUDE = -I../key_words -I../type_traits
LDFLAGS = 
LDPATH = 

PROGS = ratio_example ratio_add ratio_subtract ratio_multiply ratio_divide \
	ratio_equal ratio_not_equal ratio_less \
	ratio_less_equal ratio_greater ratio_greater_equal

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	$(QUIET) $(RM) $(PROGS) *.o *.obj *.exe
	@echo "clean OK!"

$(PROGS):%:%.cpp
	$(QUIET) $(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) $(LDPATH)

