# This is an example Makefile that works for most small/medium sized projects. It compiles every .c file in src as a .o file in 
# the build dir. You can compile with standard release -O2 optimizations with the make release command and (default) with dev dev flags 
# with make dev. You can remove build reminance and the old executable with make clean.

# C compiler
CC = clang

# directories
SOURCE_DIR = src
BUILD_DIR = build

# files
SRCS = $(wildcard $(SOURCE_DIR)/*.c)
OBJS = $(SRCS:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)
TARGET_EXE = brainshell

# compiler flags
CFLAGS = -Wall -Wextra -I$(SOURCE_DIR)
RELEASE_FLAGS = -O2
DEV_FLAGS = -O0 -g

# phony targets
.PHONY: all clean release dev

all: dev

release: CFLAGS += $(RELEASE_FLAGS)
release: $(TARGET_EXE)

dev: CFLAGS += $(DEV_FLAGS)
dev: $(TARGET_EXE)

clean:
	rm -rf $(BUILD_DIR) $(TARGET_EXE)

$(TARGET_EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

