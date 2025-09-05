# ----------------------------
# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
INCLUDES = -I./include -I./src

# ----------------------------
# Carpetas
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build

# ----------------------------
# Archivos fuente de la librería
SRC = $(shell find $(SRC_DIR) -name "*.c")
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

# ----------------------------
# Archivos de test
TEST_SRC = $(shell find $(TEST_DIR) -name "*.c")

# ----------------------------
# Librería estática
LIB = $(BUILD_DIR)/libcollections.a

# ----------------------------
# Ejecutable de tests
EXEC = $(BUILD_DIR)/all_tests

# ----------------------------
# Regla genérica para compilar .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ----------------------------
# Librería
$(LIB): $(OBJ)
	ar rcs $@ $^

# ----------------------------
# Ejecutable de tests
$(EXEC): $(LIB) $(TEST_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_SRC) -L$(BUILD_DIR) -lcollections -lcunit -o $@

# ----------------------------
# Targets
.PHONY: build test valgrind clean

build: $(LIB)
	@echo "Build completed ✅"

test: $(EXEC)
	$(EXEC)

valgrind: $(EXEC)
	valgrind --leak-check=full --track-origins=yes $(EXEC)

clean:
	rm -rf $(BUILD_DIR)/*
