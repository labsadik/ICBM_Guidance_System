CC = gcc
CFLAGS = -I./include -Wall
TARGET = bin/missile_guidance
SRC_DIR = src
OBJ_DIR = obj
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: directories $(TARGET)

directories:
    @mkdir -p bin obj

 $(TARGET): $(OBJECTS)
    $(CC) $(OBJECTS) -o $@

 $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -rf $(OBJ_DIR) $(TARGET) bin

run: all
    ./$(TARGET)