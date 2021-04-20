#include "King.hpp"
#include <vector>
#include "../GameBoard.hpp"
#include <iostream>
using namespace std;

King::King(pair<int, char> pos, bool color) : Piece(pos, color) {
    hasMoved = false;
}

vector<pair<pair<int, char>, Piece*>> King::findPositions(GameBoard* gameBoard) {
    vector<pair<pair<int, char>, Piece*>> possiblePositions;
    int vx[] = {0, 0, -1, -1, -1, 1, 1, 1};
    int vy[] = {-1, 1, -1, 0, 1, -1, 0, 1};
    int i;
    for (i = 0; i < 8; i++) {
        if (inTable(this->position.first + vx[i], 
            this->position.second + vy[i], gameBoard, this)) {
                possiblePositions.push_back(make_pair(
                        make_pair(this->position.first + vx[i], 
                        this->position.second + vy[i]), this));
        }
    }
    return possiblePositions;
}

string King::getName() {
    return "K";
}