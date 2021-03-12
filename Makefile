CC=g++
CFLAGS=-Wall -Wextra -std=c++17
FILES= pieces/Piece.cpp GameBoard.cpp pieces/Pawn.cpp test.cpp

all: build run clean

build:
	$(CC) $(CFLAGS) $(FILES) -o test
clean:
	rm test
run:
	./test

