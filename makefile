
CC = gcc
CFLAGS = -g -Wall -Wpedantic -Wextra -std=c11

main.x86_64: main.o matrix.o graph.o
	$(CC) $(CFLAGS) *.o -o main.x86_64 -lm

main.o: main.c graph.h
	$(CC) $(CFLAGS) -c main.c new/new.c

graph.o: graph.c matrix.h graph.h
	$(CC) $(CFLAGS) -c graph.c

matrix.o: matrix.c matrix.h new/new.h
	$(CC) $(CFLAGS) -c matrix.c

clean:
	rm *.o main.x86_64
