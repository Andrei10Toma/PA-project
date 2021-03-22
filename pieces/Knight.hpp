#ifndef KNIGHT_H
#define KNIGHT_H
#pragma once
#include "Piece.hpp"

using namespace std;
class Knight : public Piece
{
	private:

	public:
		vector<pair<pair<int, char>, Piece*>> findPositions(GameBoard* gameBoard);
		Knight(pair<int, char> pos, bool color);
		string getName();
};
bool inTable(int x, char y, GameBoard * gameBoard);
#endif