# Makefile

RM = rm -f
CXX = g++

ifdef slience
QUIET = @
endif

std = c++98

CXXFLAGS = -Wall -g -DNDEBUG -std=$(std)
INCLUDE = -I./impl
LDFLAGS = 
LDPATH = 

PROGS = random randint randrange shuffle choice sample

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

