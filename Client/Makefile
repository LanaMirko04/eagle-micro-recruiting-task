# Compiler
CC := gcc
# Compiler flags
CFLAGS := -g -Wall -Wextra -Iinclude

# Linker flags
LDFLAGS := 

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# Main project source files
MAIN_SRC := $(wildcard $(SRC_DIR)/*.c)

# Object files
MAIN_OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(MAIN_SRC))

# Executable name
EXECUTABLE := $(BIN_DIR)/client

# Targets
all: directories $(EXECUTABLE)

$(EXECUTABLE): $(MAIN_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

directories:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean install uninstall

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
