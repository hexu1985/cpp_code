# Makefile

RM = rm -f
CC = g++

ifdef slience
QUIET = @
endif

std = c++98

CXXFLAGS = -Wall -g -DNDEBUG -std=$(std)
INCLUDE = -I. -I../key_words
LDFLAGS = 
LDPATH = 
VPATH = shared_ptr weak_ptr

PROGS = uninitialized_fill_test uninitialized_fill_n_test \
	uninitialized_copy_test uninitialized_copy_n_test \
	temporary_buffer_test allocator_test alloc_string \
	shared_ptr_defcon shared_ptr_ptrcon shared_ptr_dtrcon \
	shared_ptr_nullptrcon shared_ptr_swap shared_ptr_spcon shared_ptr_apcon \
	shared_ptr_get shared_ptr_opstar shared_ptr_oparrow shared_ptr_boolconv \
	shared_ptr_spcount shared_ptr_unique shared_ptr_asgn shared_ptr_reset \
	shared_ptr_resetptr shared_ptr_spequal shared_ptr_splt shared_ptr_inserter \
	shared_ptr_getdeleter shared_ptr_ownerbefore \
	shared_ptr_makeshared shared_ptr_allocateshared \
	static_pointer_cast dynamic_pointer_cast const_pointer_cast \
	enable_shared_from_this shared_ptr_enshared \
	shared_ptr_cnvptr shared_ptr_cnvobj \
	shared_ptr_cnvstatic shared_ptr_cnvdyn shared_ptr_cnvconst \
	shared_ptr_destdtor shared_ptr_deleter shared_ptr_exceptions \
	shared_ptr_dereference_operator \
	weak_ptr_wpdefcon weak_ptr_wpspcon weak_ptr_wpwpcon \
	weak_ptr_lock weak_ptr_expired weak_ptr_wpcount weak_ptr_wpreset \
	weak_ptr_wpswap 

PROGS11 = shared_ptr_constructor11 shared_ptr_destructor11 \
	shared_ptr_asgn11 shared_ptr_comparisions11 \
	shared_ptr_makeshared11 shared_ptr_allocateshared11 \

ifeq ($(std), c++11)
PROGS += $(PROGS11)
endif


.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	$(QUIET) $(RM) $(PROGS) $(PROGS11) *.o *.obj *.exe
	@echo "clean OK!"

%.o:%.cpp
	$(QUIET) $(CC) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

$(PROGS): %: %.o 
	$(QUIET) $(CC) -o $@ $< $(LDFLAGS) $(LDPATH) 

