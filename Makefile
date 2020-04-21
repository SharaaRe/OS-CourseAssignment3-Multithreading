
CC = g++ -std=c++11 -g
CFLAGS = -c 

all: Goodreads.out

Goodreads.out: main.o parser.o
	$(CC) -o Goodreads.out main.o parser.o

main.o: main.cpp parser.h
	$(CC) -c main.cpp

parser.o: parser.cpp parser.h
	$(CC) -c parser.cpp

clean:
	rm *.out
	rm *.o
