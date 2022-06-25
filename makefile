CC=gcc
CFLAGS=-g -Wall
OBJS=mingrep.o
BIN=main

all:$(BIN)

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main
	$(RM) $(OBJS)

mingrep: mingrep.c
	$(CC) $(CFLAGS) -c mingrep.c -o mingrep.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r main $(OBJS) *.dSYM *.DS_Store
