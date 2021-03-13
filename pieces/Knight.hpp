#ifndef KNIGHT_H
#define KNIGHT_H
#pragma once
#include "Piece.hpp"

using namespace std;
class Knight : public Piece
{
	private:

	public:
		vector<pair<int, char>> findPositions(GameBoard* gameBoard);
		Knight(pair<int, char> pos, bool color);
};
#endif