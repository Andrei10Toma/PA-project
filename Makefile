CC=g++
CFLAGS=-Wall -Wextra -std=c++17
FILES= pieces/Piece.cpp GameBoard.cpp pieces/Pawn.cpp test.cpp

all: build clean

build:
	$(CC) $(CFLAGS) $(FILES) -o test
clean:
	rm -rf test *.debug
run:
	./test

