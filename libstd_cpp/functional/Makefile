# Makefile

RM = rm -f
CC = g++

ifdef slience
QUIET = @
endif

std = c++98

CXXFLAGS = -Wall -g -DNDEBUG -std=$(std)
INCLUDE = -I../key_words
LDFLAGS = 
LDPATH = 
VPATH = impl/

PROGS = hash_test
PROGS2 = hash_c_str_test

.PHONY: all
all: $(PROGS) $(PROGS2)
	@echo "build OK!"

clean:
	$(QUIET) $(RM) $(PROGS) $(PROGS2) *.o *.obj *.exe
	@echo "clean OK!"

%.o:%.cpp
	$(QUIET) $(CC) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

$(PROGS): %: %.o 
	$(QUIET) $(CC) -o $@ $< $(LDFLAGS) $(LDPATH)

hash_c_str_test: hash_c_str_test.cpp hash_c_str.cpp
	$(QUIET) $(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

