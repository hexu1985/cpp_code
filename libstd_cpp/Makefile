# top makefile

SUBDIR := algorithm chrono circular_buffer forward_list functional \
	initializer_list key_words limits list map memory ratio system_error \
	thread type_traits unordered_map vector 

.PHONY: all 
all: TARGET = all
all: $(SUBDIR)

.PHONY: clean 
clean: TARGET = clean
clean: $(SUBDIR)

.PHONY: $(SUBDIR)
$(SUBDIR):
	$(MAKE) --directory=$@ $(TARGET)



