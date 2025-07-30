CC = gcc
CFLAGS = -Wall -Wextra -O2

LIBS = -lncurses -lm
INCLUDE = -Isrc/include

OS := $(shell uname)
TARGET = 2048

OBJ_DIR = obj
INTERFACE_OBJ_DIR = $(OBJ_DIR)/interface

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

INTERFACE_SRCS = $(wildcard src/interface/*.c)
INTERFACE_OBJS = $(INTERFACE_SRCS:src/interface/%.c=$(INTERFACE_OBJ_DIR)/%.o)

# Adds the tinfo library to the libraries if the OS is Linux.
ifeq ($(OS), Linux)
	LIBS += -ltinfo

endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) $(INTERFACE_OBJS)
	$(CC) -o $@ $^ $(LIBS)

$(OBJ_DIR):
	mkdir -p $@

$(INTERFACE_OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

$(INTERFACE_OBJ_DIR)/%.o: src/interface/%.c | $(INTERFACE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR)
	rm 2048
