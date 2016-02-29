# Makefile

AR = ar rv
RM = rm -f
MV = mv
CXX = g++

ifdef slience
QUIET = @
endif

std = c++98

CXXFLAGS = -Wall -g -DNDEBUG -std=$(std)
INCLUDE += -I. -I../type_traits -I../functional -I../key_words
LDFLAGS = -lsystem_error
LDPATH = -L./impl
VPATH = errc error_condition error_category generic_category system_category \
	error_code system_error

RELYDIR := ./impl
PROGS = errc_test error_category_test error_category_name_test \
	generic_category_test system_category_test \
	error_code_constructor_test error_code_assign_test \
	error_code_operator_bool_test error_condition_constructor_test \
	system_error_constructor_test make_error_code_test

.PHONY: all
all: $(OBJS) $(LIB) $(PROGS)
	@echo "build OK!"

.PHONY: clean
clean: TARGET = clean
clean: $(RELYDIR)
clean:
	$(QUIET) $(RM) $(OBJS) $(LIB) $(PROGS) *.o *.exe
	@echo "clean OK!"

%.o:%.cpp
	$(QUIET) $(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

$(PROGS): %: %.o $(RELYDIR)
	$(QUIET) $(CXX) -o $@ $< $(LIB) $(LDFLAGS) $(LDPATH) 

$(LIB): $(OBJS)
	$(QUIET) $(AR) $@ $?

.PHONY: $(RELYDIR)
$(RELYDIR):
	$(MAKE) --directory=$@ $(TARGET)

