
CC = gcc
CFLAGS = -g -Wall -Wpedantic -Wextra -std=c11

.PHONY: all clean

all: main.out

main.out: main.o matrix.o rref.o nullspace.o
	$(CC) $(CFLAGS) *.o -o main.out

main.o: main.c matrix.h
	$(CC) $(CFLAGS) -c main.c

nullspace.o: nullspace.c matrix.h
	$(CC) $(CFLAGS) -c nullspace.c

rref.o: rref.c matrix.h
	$(CC) $(CFLAGS) -c rref.c

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

# Delete everything except source files
clean:
	rm *.o main.out
