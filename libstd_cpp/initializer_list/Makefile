# Makefile

RM = rm -f
CXX = g++

ifdef slience
QUIET = @
endif

std = c++98

CXXFLAGS = -Wall -g -DNDEBUG -std=$(std)
INCLUDE = 
LDFLAGS = 
LDPATH = 

PROGS = constructors size begin_end

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	$(QUIET) $(RM) $(PROGS) *.o *.obj *.exe
	@echo "clean OK!"

%.o:%.cpp
	$(QUIET) $(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

$(PROGS): %: %.o 
	$(QUIET) $(CXX) -o $@ $< $(LDFLAGS) $(LDPATH) 

