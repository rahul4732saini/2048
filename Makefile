CC = gcc
CFLAGS = -Wall -O2

LIBS = -lncurses -lm
INCLUDE = -Isrc/include

OS = "$(shell uname)"

INTERFACE_OBJS = objs/interface/core.o objs/interface/shared.o\
				 objs/interface/menu.o objs/interface/board.o

OBJS = objs/main.o objs/handlers.o objs/logic.o objs/consts.o

# Adds the tinfo library to the libraries if the OS is Linux.
ifeq ($(OS), Linux)
	LIBS += -ltinfo

endif

# Ensure the obj directories exist for storing the object files.
$(shell mkdir -p objs/interface)

build: 2048

2048: $(OBJS) $(INTERFACE_OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^

objs/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

objs/interface/%.o: src/interface/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	rm -r objs/
	rm 2048
