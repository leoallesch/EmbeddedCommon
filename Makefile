# Define the target executable name and build directory
TARGET ?= test
BUILD_DIR ?= ./build

# Define the source directory
SRC_DIRS ?= src \

# Find all source files in the source directory and subdirectories
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# Include directories for headers
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Compiler flags
CFLAGS += -std=c11 -pedantic
CPPFLAGS += $(INC_FLAGS) -MMD -MP -g -Wall -Wextra -Wcast-qual -Werror
CXXFLAGS += -std=c++17
LDFLAGS := 
#LDLIBS := -lstdc++ -lCppUTest -lCppUTestExt -lm
LDLIBS :=

# Build dependencies
BUILD_DEPS += $(MAKEFILE_LIST)

# Main target
.PHONY: all 

all: $(BUILD_DIR)/$(TARGET)

# Run target
.PHONY: run
run: all
	@echo Running $(BUILD_DIR)/$(TARGET)...
	@$(BUILD_DIR)/$(TARGET)

# Linking target
$(BUILD_DIR)/$(TARGET): $(OBJS)
	@echo Linking $@...
	@mkdir -p $(dir $@)
	@$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

# Assembling target
$(BUILD_DIR)/%.s.o: %.s $(BUILD_DEPS)
	@echo Assembling $<...
	@mkdir -p $(dir $@)
	@$(AS) $(ASFLAGS) -c $< -o $@

# Compiling C source files
$(BUILD_DIR)/%.c.o: %.c $(BUILD_DEPS)
	@echo Compiling $<...
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Compiling C++ source files
$(BUILD_DIR)/%.cpp.o: %.cpp $(BUILD_DEPS)
	@echo Compiling $<...
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Clean target
.PHONY: clean
clean:
	@echo Cleaning...
	@rm -rf $(BUILD_DIR)

# Include dependency files
-include $(DEPS)
