CC=g++
CFLAGS=-Wall -Wextra -std=c++17

all: build run clean

build:
	$(CC) $(CFLAGS) test.cpp -o test
clean:
	rm test
run:
	./test

