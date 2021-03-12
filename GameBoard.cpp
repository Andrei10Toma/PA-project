//
// Created by andrei on 11.03.2021.
//

#include "GameBoard.hpp"
#include "pieces/Piece.hpp"
#include "pieces/Pawn.hpp"

void GameBoard::init() {
    for (int i = 0; i < 8; i++) {
        this->table[2][i + 1] = new Pawn(make_pair(2, 'a' +  i ), 1);
        this->table[7][i + 1] = new Pawn(make_pair(2, 'a' +  i ), 0);
    }
}
