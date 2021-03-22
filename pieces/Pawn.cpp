#include "Pawn.hpp"
#include <vector>
#include "../GameBoard.hpp"
#include <iostream>
using namespace std;

Pawn::Pawn(pair<int, char> pos, bool color) : Piece(pos, color) {
}

vector<pair<pair<int, char>, Piece*>> Pawn::findPositions(GameBoard* gameBoard) {
    vector<pair<pair<int, char>, Piece*>> possiblePositions;
    if (this->color == 1) {
        if (this->position.first == 2) {
            if (gameBoard->table[3][this->position.second - 'a' + 1] == NULL) {
                possiblePositions.push_back(make_pair(make_pair(3, this->position.second), this));
            }
            if (gameBoard->table[3][this->position.second - 'a' + 1] == NULL && gameBoard->table[4][this->position.second - 'a' + 1] == NULL) {
                possiblePositions.push_back(make_pair(make_pair(4, this->position.second), this));
            }
        }
        else {
            if (position.first + 1 < 9) {
                if (position.second - 'a' + 1 < 9) {
                    if (gameBoard->table[position.first + 1][position.second - 'a' + 1] == NULL) {
                        possiblePositions.push_back(make_pair(make_pair(position.first + 1, position.second), this));
                    }
                }
                if (position.second - 'a' > 0) {
                    if (gameBoard->table[position.first + 1][position.second - 'a' ] != NULL) {
                        if (gameBoard->table[position.first + 1][position.second - 'a' ]->color != this->color)
                            possiblePositions.push_back(make_pair(make_pair(position.first + 1, position.second - 1), this));
                    }
                }
                if (position.second - 'a' + 2 < 9) {
                    if (gameBoard->table[position.first + 1][position.second - 'a' + 2 ] != NULL) {
                        if (gameBoard->table[position.first + 1][position.second - 'a' + 2 ]->color != this->color)
                            possiblePositions.push_back(make_pair(make_pair(position.first + 1, position.second + 1), this));
                    }
                }
            }
        }
    }
    return possiblePositions;
}

string Pawn::getName() {
    return "P";
}