#ifndef BISHOP_H
#define BISHOP_H
#pragma once
#include "Piece.hpp"
using namespace std;

class Bishop : public Piece {
    private:

    public:
        vector<pair<pair<int, char>, Piece*>> findPositions(GameBoard* gameBoard);
        Bishop(pair<int, char> pos, bool color);
};
#endif