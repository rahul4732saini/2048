CC = gcc
CFLAGS = -Wall -Wextra -MMD -O2

LIBS = -lncurses -lm
INCLUDE = -Isrc/include

OS := $(shell uname)
TARGET := 2048

SRC_DIR := src
SRCS := $(wildcard $(SRC_DIR)/*.c)

INTERFACE_SRC_DIR := $(SRC_DIR)/interface
INTERFACE_SRCS := $(wildcard $(INTERFACE_SRC_DIR)/*.c)

OBJ_DIR := obj
OBJS := $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

INTERFACE_OBJ_DIR := $(OBJ_DIR)/interface
INTERFACE_OBJS := $(INTERFACE_SRCS:src/interface/%.c=$(INTERFACE_OBJ_DIR)/%.o)

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

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

$(INTERFACE_OBJ_DIR)/%.o: $(INTERFACE_SRC_DIR)/%.c | $(INTERFACE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

# Includes the dependency files for tracking header files.
-include $(OBJS:%.o=%.d) $(INTERFACE_OBJS:%.o=%.d)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET)
