//
// Created by andrei on 11.03.2021.
//

#include "Piece.hpp"
#include "../GameBoard.hpp"
#include <iostream>
using namespace std;

Piece::Piece(pair<int, char> pos, bool color) {
    this->color = color;
    this->position = pos;
}
bool inTable(int x, char y, GameBoard * gameBoard){
    cout << x << ' ' << y << endl;
    if(x >= 9 || x <= 0 || y < 'a' || y > 'h')
        return false;
    if(gameBoard->table[x][y - 'a' + 1] != NULL && gameBoard->table[x][y - 'a' + 1]->color == 1)
        return false;
    return true;
}