
CC = g++ -std=c++11 -g
CFLAGS = -c 

all: Goodreads.out

test: test.out

test.out: test.o Book.o parser.o
	$(CC) -o test.out test.o Book.o parser.o


Goodreads.out: main.o parser.o Book.o
	$(CC) -o Goodreads.out main.o parser.o Book.o

Book.o: Book.cpp Book.h parser.h
	$(CC) $(CFLAGS) Book.cpp

main.o: main.cpp parser.h
	$(CC) -c main.cpp

parser.o: parser.cpp parser.h
	$(CC) -c parser.cpp

clean:
	rm *.o
	rm *.out
