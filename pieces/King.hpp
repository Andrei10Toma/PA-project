#ifndef KING_H
#define KING_H
#pragma once
#include "Piece.hpp"
#include "Knight.hpp"

using namespace std;
class King : public Piece
{
	private:

	public:
		bool hasMoved;
		vector<pair<pair<int, char>, Piece*>> findPositions(GameBoard* gameBoard);
		King(pair<int, char> pos, bool color);
		string getName();
};
#endif