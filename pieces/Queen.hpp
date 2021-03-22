#ifndef QUEEN_H
#define QUEEN_H
#pragma once
#include "Piece.hpp"
#include <vector>
	
class Queen : public Piece
{
	private:

	public:
		vector<pair<int, char>> findPositions(GameBoard* gameBoard);
		Queen(pair<int, char> pos, bool color);
		string getName();
};
#endif