#include "Pawn.hpp"
#include <vector>
using namespace std;

Pawn::Pawn(pair<int, char> pos, bool color) : Piece(pos, color) {
}

vector<pair<int, char>> Pawn::findPositions(GameBoard gameBoard) {
    vector<pair<int, char>> possiblePositions;
    if (this->color == 1) {
        if (this->position.first == 2) {
            if (gameBoard.table[4][position.second] == NULL) {
                possiblePositions.push_back(make_pair(4, position.second));
            }
            if (gameBoard.table[3][position.second] == NULL) {
                possiblePositions.push_back(make_pair(3, position.second));
            }
        }
        else {
            if (gameBoard.table[position.first - 1][position.second] == NULL) {
                possiblePositions.push_back(make_pair(position.first - 1, position.second));
            }
        }
    }
    return possiblePositions;
}