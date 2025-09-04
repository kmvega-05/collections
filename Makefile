# ----------------------------
# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
INCLUDES = -I./src -I./src/common -I./src/vector

# ----------------------------
# Carpetas
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build

# ----------------------------
# Fuentes de la librería
SRC = $(SRC_DIR)/common/common.c \
      $(SRC_DIR)/common/common_test.c \
      $(SRC_DIR)/vector/vector.c

# ----------------------------
# Objetos de la librería
OBJ = $(BUILD_DIR)/common.o \
      $(BUILD_DIR)/common_test.o \
      $(BUILD_DIR)/vector.o

# ----------------------------
# Archivos de test
TEST_SRC = $(wildcard $(TEST_DIR)/**/*.c)

# ----------------------------
# Ejecutable de tests
EXEC = $(BUILD_DIR)/all_tests

# ----------------------------
# Crear carpeta build si no existe
$(shell mkdir -p $(BUILD_DIR))

# ----------------------------
# Build objetos de la librería
$(BUILD_DIR)/common.o: $(SRC_DIR)/common/common.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/common_test.o: $(SRC_DIR)/common/common_test.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/vector.o: $(SRC_DIR)/vector/vector.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ----------------------------
# Build total
.PHONY: build
build: $(OBJ)
	@echo "Build completed"

# ----------------------------
# Limpiar compilados
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*

# ----------------------------
# Test: compila y ejecuta todos los tests
.PHONY: test
test: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) \
		$(OBJ) $(TEST_SRC) $(TEST_DIR)/main.c \
		-o $(EXEC) -lcunit
	$(EXEC)

# ----------------------------
# Valgrind
.PHONY: valgrind
valgrind: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) \
		$(OBJ) $(TEST_SRC) $(TEST_DIR)/main.c \
		-o $(EXEC) -lcunit
	valgrind --leak-check=full --track-origins=yes $(EXEC)
