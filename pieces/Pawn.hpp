#ifndef PAWN_H
#define PAWN_H
#pragma once
#include "Piece.hpp"

using namespace std;
	
class Pawn : public Piece
{
private:

public:
    vector<pair<int, char>> findPositions(GameBoard* gameBoard);
	Pawn(pair<int, char> pos, bool color);
};
#endif