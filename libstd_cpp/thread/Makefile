# Makefile

AR = ar r
RM = rm -f
MV = mv
CXX = g++

ifdef slience
QUIET = @
endif

std = c++98

CXXFLAGS = -Wall -g -DNDEBUG -std=$(std)
INCLUDE += -I. -I../system_error -I../type_traits -I../chrono -I../limits \
	-I../ratio -I../key_words -I../functional
LDFLAGS = -lthread -lsystem_error -lpthread
LDPATH = -L./impl -L../system_error/impl
VPATH = call_once lock condition_variable lock_guard notify_all_at_thread_exit \
	timed_mutex condition_variable_any lock_options recursive_mutex \
	try_lock this_thread mutex thread recursive_timed_mutex unique_lock \
	shared_mutex

RELYDIR := ../system_error/impl ./impl
PROGS = thread_constructor_test thread_operator_assign_test \
	thread_get_id_test thread_joinable_test thread_join_test \
	thread_detach_test thread_native_handle_test \
	thread_hardware_concurrency_test \
	this_thread_get_id_test this_thread_yield_test \
	this_thread_sleep_for_test this_thread_sleep_until_test \
	mutex_lock_test mutex_unlock_test mutex_try_lock_test \
	recursive_mutex_lock_test \
	recursive_mutex_unlock_test \
	recursive_mutex_try_lock_test \
	timed_mutex_try_lock_for_test \
	timed_mutex_try_lock_until_test \
	recursive_timed_mutex_lock_test \
	recursive_timed_mutex_unlock_test \
	recursive_timed_mutex_try_lock_test \
	recursive_timed_mutex_try_lock_for_test \
	recursive_timed_mutex_try_lock_until_test \
	unique_lock_test lock_guard_test lock_options_test \
	lock_test try_lock_test call_once_test \
	condition_variable_wait_test \
	condition_variable_wait_for_test \
	condition_variable_wait_until_test \
	condition_variable_notify_one_test \
	condition_variable_notify_all_test \
	condition_variable_any_wait_test \
	condition_variable_any_wait_for_test \
	condition_variable_any_wait_until_test \
	condition_variable_any_notify_one_test \
	condition_variable_any_notify_all_test \
	notify_all_at_thread_exit_test \
	shared_mutex_test

PROGS11 = recursive_mutex_is_standard_layout

ifeq ($(std), c++11)
PROGS += $(PROGS11)
endif

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

.PHONY: clean
clean: TARGET = clean
clean: $(RELYDIR)
clean:
	$(QUIET) $(RM) $(PROGS) $(PROGS11) *.o *.exe *.obj 
	@echo "clean OK!"

$(PROGS): %: %.cpp $(LIB) $(RELYDIR)
	$(QUIET) $(CXX) -o $@ $< $(CXXFLAGS) $(INCLUDE) $(LDPATH) $(LDFLAGS)

.PHONY: $(RELYDIR)
$(RELYDIR):
	$(MAKE) --directory=$@ $(TARGET)

