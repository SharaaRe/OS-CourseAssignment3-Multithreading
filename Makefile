
CC = g++ -std=c++11 -g
CFLAGS = -c 

all: Goodreads.out

Goodreads.out: main.o Goodreads.o Book.o
	$(CC)  -o Goodreads.out main.o Goodreads.o Book.o -lpthread

main.o: main.cpp
	$(CC) -c main.cpp

Goodreads.o: Goodreads.cpp Goodreads.h Book.h
	$(CC) $(CFLAGS) Goodreads.cpp

Book.o: Book.cpp Book.h 
	$(CC) $(CFLAGS) Book.cpp



clean:
	rm *.o
	rm *.out
