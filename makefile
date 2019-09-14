
CC = gcc
CFLAGS = -g -Wall -Wpedantic -Wextra -std=c11

main.out: main.o matrix.o rref.o
	$(CC) $(CFLAGS) *.o -o main.out

main.o: main.c matrix.h
	$(CC) $(CFLAGS) -c main.c

rref.o: rref.c matrix.h
	$(CC) $(CFLAGS) -c rref.c

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

clean:
	rm *.o main.out
