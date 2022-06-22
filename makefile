CC=gcc
CFLAGS=-g -Wall
OBJS=mingrep.o
BIN=main

all:$(BIN)

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main

mingrep: mingrep.c
	$(CC) $(CFLAGS) -c mingrep.c -o mingrep.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r main *.o *.dSYM *.DS_Store
