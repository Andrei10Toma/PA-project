#ifndef ROOK_H
#define ROOK_H
#pragma once
#include "Piece.hpp"
using namespace std;

class Rook : public Piece {
    private:

    public:
      bool hasMoved;
      vector<pair<pair<int, char>, Piece*>> findPositions(GameBoard* gameBoard);
      Rook(pair<int, char> pos, bool color);
      string getName();
};
#endif