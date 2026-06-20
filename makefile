CC = gcc
CFLAGS = -Wall -Wextra -g -pthread
OBJ = main.o mainLoop.o Utils.o structUtils.o threadUtils.o

all: main

main: $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)

main.o: main.c header.h
mainLoop.o: mainLoop.c header.h
Utils.o: Utils.c header.h
structUtils.o: structUtils.c header.h
threadUtils.o: threadUtils.c header.h

clean:
	rm -f $(OBJ) main

.PHONY: all clean
