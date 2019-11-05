
CC = gcc
CFLAGS = -g -Wall -Wpedantic -Wextra -std=c11

.PHONY: all clean

all: main.out

main.out: main.o matrix.o rref.o regression.o util.o
	$(CC) $(CFLAGS) *.o -o main.out

main.o: main.c matrix.h util.h
	$(CC) $(CFLAGS) -c main.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c

regression.o: regression.c matrix.h util.h
	$(CC) $(CFLAGS) -c regression.c

rref.o: rref.c matrix.h util.h
	$(CC) $(CFLAGS) -c rref.c

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

# Delete everything except source files
clean:
	rm *.o main.out
