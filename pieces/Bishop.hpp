#ifndef BISHOP_H
#define BISHOP_H
#pragma once
#include "Piece.hpp"
using namespace std;

class Bishop : public Piece {
    private:

    public:
        vector<pair<int, char>> findPositions(GameBoard* gameBoard);
        Bishop(pair<int, char> pos, bool color);
        string getName();
};
#endif