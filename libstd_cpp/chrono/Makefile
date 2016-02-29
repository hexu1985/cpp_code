# Makefile

RM = rm -f
CXX = g++

ifdef slience
QUIET = @
endif

std = c++98

CXXFLAGS = -Wall -g -DNDEBUG -std=$(std)
INCLUDE = -I. -I../common -I../ratio -I../type_traits -I../limits -I../key_words
LDFLAGS = 
LDPATH = 
VPATH = duration steady_clock system_clock time_point

PROGS = duration_arithmetic duration_compare duration_compound_assign \
	duration_constructor duration_count duration_cast duration_example \
	duration_inc_dec duration_min_max duration_operators duration_pos_neg \
	duration_zero time_point_cast time_point_constructor time_point_operators \
	time_point_time_since_epoch system_clock_from_time_t system_clock_now \
	system_clock_example system_clock_to_time_t steady_clock_now

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

