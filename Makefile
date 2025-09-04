# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
INCLUDES = -I./src -I./src/common -I./src/vector

# Carpetas
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build

# Fuentes de la librería
SRC = $(SRC_DIR)/common/common.c \
      $(SRC_DIR)/common/common_test.c \
      $(SRC_DIR)/vector/vector.c

# Todos los archivos de test excepto main.c
TEST_SRC = $(filter-out $(TEST_DIR)/main.c,$(wildcard $(TEST_DIR)/**/*.c))

# Objetos
OBJ = $(BUILD_DIR)/common.o $(BUILD_DIR)/common_test.o $(BUILD_DIR)/vector.o

# Ejecutable de tests
EXEC = $(BUILD_DIR)/all_tests

# Crear carpeta build si no existe
$(shell mkdir -p $(BUILD_DIR))

# ----------------------------
# Build objetos
$(BUILD_DIR)/common.o: $(SRC_DIR)/common/common.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/common_test.o: $(SRC_DIR)/common/common_test.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/vector.o: $(SRC_DIR)/vector/vector.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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
test:
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) $(TEST_SRC) $(TEST_DIR)/main.c -o $(EXEC) -lcunit
	$(EXEC)

# Valgrind
.PHONY: valgrind
valgrind:
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) $(TEST_SRC) $(TEST_DIR)/main.c -o $(EXEC) -lcunit
	valgrind --leak-check=full --track-origins=yes $(EXEC)

