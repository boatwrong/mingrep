CC=gcc-12
CFLAGS=-g -Wall
OBJS=helper.o
BIN=mingrep

all: $(BIN)

%.0: %.c %.h
	$(CC) $(CFLAGS) -c $^

mingrep: helper.o mingrep.c
	$(CC) $(CFLAGS) -o $@ $^

# test: test.c
# 	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) -r mingrep test *.o *.dSYM *.DS_Store *.gch

cleanup:
	$(RM) -r test *.o *.dSYM *.DS_Store *.gch
