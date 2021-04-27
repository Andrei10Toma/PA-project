#ifndef PAWN_H
#define PAWN_H
#pragma once
#include "Piece.hpp"

using namespace std;
	
class Pawn : public Piece
{
private:

public:
    bool moved_two;
    int moveNumber;
    vector<pair<pair<int, char>, Piece*>> findPositions(GameBoard* gameBoard);
	Pawn(pair<int, char> pos, bool color);
    int promote(GameBoard* gameBoard, vector<Piece*>& pieces,
        char promotionPiece);
    string getName();
};
#endif