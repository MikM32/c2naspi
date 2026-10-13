# ============================================================
#  Makefile para c2mada
#  - Compila todos los .c de src/
#  - Genera el ejecutable c2mada.out en la raíz del proyecto
#  - Soporta: make all, make clean, make run, make rebuild
# ============================================================

# --- Herramientas ---
CC      := cc
RM      := rm -rf

# --- Directorios ---
SRC_DIR   := src
INC_DIR   := include
BUILD_DIR := build

# --- Flags de compilación ---
# -I$(INC_DIR)  -> los headers se buscan en include/
# -MMD -MP      -> generan archivos .d con dependencias de headers
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -O2 -g \
           -I$(INC_DIR) -MMD -MP

# Flags de enlazado (añade aquí -lm, -lpthread, etc. si los necesitas)
LDFLAGS :=
LDLIBS  :=

# --- Nombre del ejecutable ---
TARGET := c2mada.out

# --- Descubrir fuentes y objetos automáticamente ---
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# ============================================================
#  Reglas
# ============================================================

.PHONY: all clean run rebuild

# --- all: compila el ejecutable ---
all: $(TARGET)

# --- Enlazado final ---
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

# --- Compilación de cada .c a .o ---
# $< = fuente, $@ = objeto, $@.d = archivo de dependencias
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Crear el directorio build/ si no existe ---
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# --- clean: borra objetos, dependencias y el ejecutable ---
clean:
	$(RM) $(BUILD_DIR) $(TARGET)

# --- rebuild: limpia y recompila todo ---
rebuild: clean all

# --- run: compila y ejecuta ---
run: all
	./$(TARGET)

# --- Incluir dependencias generadas por -MMD -MP ---
# El '-' evita errores si los .d aún no existen
-include $(DEPS)
