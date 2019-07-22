
CC = clang
CFLAGS = -g -Wall -Wpedantic -Wextra

main.x86_64: main.o matrix.o graph.o
	time $(CC) $(CFLAGS) *.o -o main.x86_64 -lm

main.o: main.c graph.h
	time $(CC) $(CFLAGS) -c main.c new/new.c

graph.o: graph.c matrix.h graph.h
	time $(CC) $(CFLAGS) -c graph.c

matrix.o: matrix.c matrix.h new/new.h
	time $(CC) $(CFLAGS) -c matrix.c

clean:
	rm *.o main.x86_64
