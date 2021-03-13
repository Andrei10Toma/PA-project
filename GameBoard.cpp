//
// Created by andrei on 11.03.2021.
//

#include "GameBoard.hpp"
#include "pieces/Piece.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Rook.hpp"

void GameBoard::init() {
    //PAWNS
    for (int i = 0; i < 8; i++) {
        this->table[2][i + 1] = new Pawn(make_pair(2, 'a' +  i ), 1);
        this->table[7][i + 1] = new Pawn(make_pair(7, 'a' +  i ), 0);
    }
    //KNIGHTS
    this->table[1][2] = new Knight(make_pair(1, 'b'), 1);
    this->table[1][7] = new Knight(make_pair(1, 'g'), 1);
    this->table[8][2] = new Knight(make_pair(8, 'b'), 0);
    this->table[8][7] = new Knight(make_pair(8, 'g'), 0);

    //ROOKS
    this->table[1][1] = new Rook(make_pair(1, 'a'), 1);
    this->table[1][8] = new Rook(make_pair(1, 'h'), 1);
    this->table[8][1] = new Rook(make_pair(8, 'a'), 0);
    this->table[8][8] = new Rook(make_pair(8, 'h'), 0);


}
