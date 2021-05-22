//
// Created by andrei on 11.03.2021.
//

#include "GameBoard.hpp"
#include "pieces/Piece.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Queen.hpp"
#include "pieces/Rook.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/King.hpp"
#include <iostream>

void GameBoard::init(vector<Piece*> &white, vector<Piece*> &black) {
    // Clean vectors;
    while(white.size() > 0)
        white.pop_back();
    while(black.size() > 0)
        black.pop_back();

    // RESET
    for (int i = 0; i < 8; i++) 
        for(int j = 0; j < 8; j++)
            this->table[i+1][j+1] = NULL;
    // PAWNS
    for (int i = 0; i < 8; i++) {
        this->table[2][i + 1] = new Pawn(make_pair(2, 'a' +  i ), 1);
        black.push_back(this->table[2][i + 1]);
        this->table[7][i + 1] = new Pawn(make_pair(7, 'a' +  i ), 0);
        white.push_back(this->table[7][i + 1]);
    }
    // KNIGHTS
    this->table[1][2] = new Knight(make_pair(1, 'b'), 1);
    this->table[1][7] = new Knight(make_pair(1, 'g'), 1);
    black.push_back(this->table[1][2]);
    black.push_back(this->table[1][7]);
    this->table[8][2] = new Knight(make_pair(8, 'b'), 0);
    this->table[8][7] = new Knight(make_pair(8, 'g'), 0);
    white.push_back(this->table[8][2]);
    white.push_back(this->table[8][7]);

    // QUEENS
    this->table[1][4] = new Queen(make_pair(1, 'd'), 1);
    black.push_back(this->table[1][4]);
    this->table[8][4] = new Queen(make_pair(8, 'd'), 0);
    white.push_back(this->table[8][4]);

    // ROOKS
    this->table[1][1] = new Rook(make_pair(1, 'a'), 1);
    this->table[1][8] = new Rook(make_pair(1, 'h'), 1);
    black.push_back(this->table[1][1]);
    black.push_back(this->table[1][8]);
    this->table[8][1] = new Rook(make_pair(8, 'a'), 0);
    this->table[8][8] = new Rook(make_pair(8, 'h'), 0);
    white.push_back(this->table[8][1]);
    white.push_back(this->table[8][8]);

    // BISHOPS
    this->table[1][3] = new Bishop(make_pair(1, 'c'), 1);
    this->table[1][6] = new Bishop(make_pair(1, 'f'), 1);
    black.push_back(this->table[1][3]);
    black.push_back(this->table[1][6]);
    this->table[8][3] = new Bishop(make_pair(8, 'c'), 0);
    this->table[8][6] = new Bishop(make_pair(8, 'f'), 0);
    white.push_back(this->table[8][3]);
    white.push_back(this->table[8][6]);

    // KINGS
    this->table[1][5] = new King(make_pair(1, 'e'), 1);
    black.push_back(this->table[1][5]);
    this->table[8][5] = new King(make_pair(8, 'e'), 0);
    white.push_back(this->table[8][5]);
}

void GameBoard::showBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (this->table[i + 1][j + 1] != NULL) {
                cout << this->table[i + 1][j + 1]->name << this->table[i + 1][j + 1]->color << '\t';
            }
            else {
                cout << "-\t";
            }
        }
        cout << endl;
    }
}
