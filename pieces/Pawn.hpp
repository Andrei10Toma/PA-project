#ifndef PAWN_H
#define PAWN_H
#pragma once
#include "Piece.hpp"

using namespace std;
	
class Pawn : public Piece
{
private:

public:
    vector<pair<pair<int, char>, Piece*>> findPositions(GameBoard* gameBoard);
	Pawn(pair<int, char> pos, bool color);
    int promoteToQueen(GameBoard* gameBoard);
    string getName();
};
#endif