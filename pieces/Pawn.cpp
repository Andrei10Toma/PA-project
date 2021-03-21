#include "Pawn.hpp"
#include <vector>
#include "../GameBoard.hpp"
#include <iostream>
using namespace std;

Pawn::Pawn(pair<int, char> pos, bool color) : Piece(pos, color) {
}

vector<pair<int, char>> Pawn::findPositions(GameBoard* gameBoard) {
    vector<pair<int, char>> possiblePositions;
    if (this->position.first == 2) {
        if (gameBoard->table[4][position.second - 'a' + 1] == NULL) {
            possiblePositions.push_back(make_pair(4, position.second));
            }
        if (gameBoard->table[3][position.second - 'a' + 1] == NULL) {
                possiblePositions.push_back(make_pair(3, position.second));
        }
    }
    else {
        if (gameBoard->table[position.first + 1][position.second - 'a' + 1] == NULL) {
                possiblePositions.push_back(make_pair(position.first + 1, position.second));
        }
        if (gameBoard->table[position.first + 1][position.second - 'a' ] != NULL) {
            possiblePositions.push_back(make_pair(position.first + 1, position.second - 1));
        }
        if (gameBoard->table[position.first + 1][position.second - 'a' + 2 ] != NULL) {
            possiblePositions.push_back(make_pair(position.first + 1, position.second + 1));
        }
    }
    return possiblePositions;
}