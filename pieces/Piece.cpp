//
// Created by andrei on 11.03.2021.
//

#include "Piece.hpp"

using namespace std;

Piece::Piece(pair<int, char> pos, bool color) {
    this->color = color;
    this->position = pos;
}
