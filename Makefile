CC = gcc

DATA_FILE = data/prime.csv
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
TARGET = $(BUILD_DIR)/main

DEBUG = -DDEBUG -g
C_SOURCES = $(shell find $(SRC_DIR) -type f -name "*.c")
C_INCLUDES = $(shell find $(INC_DIR) -type d -printf "-I%p ")

O_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SOURCES))
C_FLAGS = -Wall -std=c23 -O2 $(C_INCLUDES)
BUILD_DIRS = $(sort $(dir $(O_FILES)))

DEFAULT_GOAL := help

.PHONY: help test all debug dall clean run print

help:
	@awk 'BEGIN {FS = ":.*##"; printf "\nAvailable commands:\n"} \
	/^[a-zA-Z_-]+:.*##/ { printf "  %-15s %s\n", $$1, $$2 }' $(MAKEFILE_LIST)

test: clean all run ## everything! all! at once!

all: ## builds the whole project
	@if [ -z "$(C_SOURCES)" ]; then \
		echo "No source files found in $(SRC_DIR)"; \
		exit 1; \
	fi
	$(MAKE) $(TARGET)

$(TARGET): $(O_FILES) ## Link the target binary from object files
	$(CC) $(C_FLAGS) -o $@ $^

# Rule to compile each .c file into a .o file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIRS)
	$(CC) $(C_FLAGS) -c $< -o $@

# Rule to create necessary directories for object files
$(BUILD_DIRS):
	mkdir -p $@

debug: clean dall run ## clean, compile with debug, run

dall: ## compile with debug
	$(CC) $(C_FLAGS) $(DEBUG) $(C_SOURCES) -o $(TARGET)

clean: ## clean the project files
	rm -rf $(BUILD_DIR)

run: ## run the program
	./$(TARGET) $(DATA_FILE)

$(info Sources: $(C_SOURCES))
$(info Include Flags: $(C_INCLUDES))
