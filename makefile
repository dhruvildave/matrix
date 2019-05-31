
CC = clang
CFLAGS = -g -Wall -Wpedantic -Wextra

main.out: main.o matrix.o
	time $(CC) $(CFLAGS) *.o -o main.out -lm

main.o: main.c matrix.h pch.h
	time $(CC) $(CFLAGS) -c main.c

matrix.o: matrix.c matrix.h pch.h
	time $(CC) $(CFLAGS) -c matrix.c

clean:
	rm *.o main.out
