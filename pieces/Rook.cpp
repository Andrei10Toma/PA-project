#include "Rook.hpp"
#include <vector>
#include "../GameBoard.hpp"
#include <iostream>
using namespace std;

Rook::Rook(pair<int, char> pos, bool color) : Piece(pos, color) {
}

vector<pair<int, char>> Rook::findPositions(GameBoard* gameBoard) {
    vector<pair<int, char>> possiblePositions;
    int currentLine = this->position.first;
    char currentColumn = this->position.second;
    if (this->color == 1) {
        int line;
        for (line = 1; line < 9 && line != currentLine; line++) {
            if (gameBoard->table[line][currentColumn - 'a' + 1] == NULL) {
                possiblePositions.push_back(make_pair(line, currentColumn));
            }
        }
        char col;
        for (col = 'a'; col < 'i' && col != currentColumn; col++) {
            if (gameBoard->table[currentLine][col - 'a' + 1] == NULL) {
                possiblePositions.push_back(make_pair(currentLine, col));
            }
        }
    }

    return possiblePositions;
}