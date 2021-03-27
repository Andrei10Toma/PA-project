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
    // for the warning
    gameBoard->table[1][1] = gameBoard->table[1][1];
    return possiblePositions;
}

string King::getName() {
    return "K";
}