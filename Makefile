##
 # MIT License
 #
 # Copyright (c) 2024 Leon Cotten
 #
 # This language is provided under the MIT Licence.
 # See LICENSE for more information.
 ##

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
.PHONY: all clean release dev install remove

all: dev

release: CFLAGS += $(RELEASE_FLAGS)
release: $(TARGET_EXE)

dev: CFLAGS += $(DEV_FLAGS)
dev: $(TARGET_EXE)

clean:
	rm -rf $(BUILD_DIR) $(TARGET_EXE)

install: $(TARGET_EXE)
	cp $(TARGET_EXE) /usr/bin

remove:
	rm /usr/bin/$(TARGET_EXE)

$(TARGET_EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

