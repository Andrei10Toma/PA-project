#ifndef ROOK_H
#define ROOK_H
#pragma once
#include "Piece.hpp"
using namespace std;

class Rook : public Piece {
    private:

    public:
		vector<pair<int, char>> findPositions(GameBoard* gameBoard);
        Rook(pair<int, char> pos, bool color);
        string getName();
};
#endif