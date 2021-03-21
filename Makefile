CC=g++
CFLAGS=-Wall -Wextra -std=c++17
FILES= pieces/Piece.cpp GameBoard.cpp pieces/Pawn.cpp pieces/Knight.cpp pieces/Rook.cpp pieces/Bishop.cpp test2.cpp

all: build run

build:
	$(CC) $(CFLAGS) $(FILES) -o test
clean:
	rm -rf test *.debug
run:
	./test

