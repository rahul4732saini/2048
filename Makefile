CC = gcc
CFLAGS = -Wall -Wextra -O2

LIBS = -lncurses -lm
INCLUDE = -Isrc/include

OS := $(shell uname)

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=objs/%.o)

INTERFACE_SRCS = $(wildcard src/interface/*.c)
INTERFACE_OBJS = $(INTERFACE_SRCS:src/interface/%.c=objs/interface/%.o)

# Adds the tinfo library to the libraries if the OS is Linux.
ifeq ($(OS), Linux)
	LIBS += -ltinfo

endif

.PHONY: all clean

# Ensure the obj directories exist for storing the object files.
$(shell mkdir -p objs/interface)

all: create_dir 2048

2048: $(OBJS) $(INTERFACE_OBJS)
	$(CC) -o $@ $^ $(LIBS)

objs/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

objs/interface/%.o: src/interface/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	rm -r objs/
	rm 2048
