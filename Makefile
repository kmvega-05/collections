# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
LDFLAGS = -lcunit

# Carpetas
SRC_DIR = src
TEST_DIR = test
OBJ_DIR = build
LIB_DIR = lib

# Librería
LIB_NAME = $(LIB_DIR)/libcollections.a
LIB_SRCS = $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c)
LIB_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(LIB_SRCS))

# Tests
TEST_SRCS = $(TEST_DIR)/main.c $(wildcard $(TEST_DIR)/vector/*.c)
TEST_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(TEST_SRCS))
TEST_BIN = $(OBJ_DIR)/test_runner

# Crear carpetas necesarias
$(shell mkdir -p $(OBJ_DIR) $(LIB_DIR))

# Default target
build: $(LIB_NAME) $(TEST_BIN)
	@echo "✅ Build completado correctamente."

# Compilar librería estática
$(LIB_NAME): $(LIB_OBJS)
	ar rcs $@ $^

# Compilar objetos de la librería y tests
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Linkear binario de tests dentro de build/
$(TEST_BIN): $(LIB_NAME) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) -L$(LIB_DIR) -lcollections $(LDFLAGS) -o $@

# Ejecutar tests directamente
test: $(TEST_BIN)
	@./$(TEST_BIN)
	@echo "✅ Tests ejecutados correctamente."

# Ejecutar tests con Valgrind
memcheck: $(TEST_BIN)
	@valgrind --leak-check=full ./$(TEST_BIN)
	@echo "✅ Memcheck ejecutado correctamente."

# Limpiar
clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR)
	@echo "🧹 Proyecto limpiado correctamente."
