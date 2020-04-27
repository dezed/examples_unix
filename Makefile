CC=gcc
CXX=g++

BUILD_DIR ?= ./build
SRC_DIRS ?= .

SRCS := source/list.c source/set.c source/queue.c source/bistree.c source/dlist.c source/stack.c source/heap.c source/events.c

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o) 
DEPS := $(OBJS:.o=.d)

INC_FLAGS := -I. -I../include

CFLAGS = -g -Wall -I. -I./include
CPPFLAGS = -fPIC
#LDFLAGS = 


#all:libcsal
all:$(BUILD_DIR)/libmac

$(BUILD_DIR)/libmac: $(OBJS) 
	@$(MKDIR_P) $(BUILD_DIR)
	$(CXX) -g -shared -fPIC $(OBJS) -o $@.so $(LDFLAGS) 

# c source
$(BUILD_DIR)/%.c.o: %.c 
	@$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# cpp source
$(BUILD_DIR)/%.cpp.o: %.cpp 
	@$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

#test:
#	gcc -g ./test/main.c $(CFLAGS) $(LDFLAGS) -lcsal -o $(BUILD_DIR)/test 

.PHONY: clean  
	test: 
	echo $(OS) 
clean: 
	 $(RM) -r $(BUILD_DIR) 

-include $(DEPS)

MKDIR_P ?= mkdir -p
