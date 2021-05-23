//
// Created by andrei on 11.03.2021.
//

#ifndef PA_PROJECT_GAMEBOARD_H
#define PA_PROJECT_GAMEBOARD_H

#include <vector>
#include "pieces/Piece.hpp"
#include "pieces/King.hpp"

using namespace std;

class GameBoard {
public:
    Piece* table[9][9];
    void init(vector<Piece*> &white, vector<Piece*> &black);
    void showBoard();
};


#endif //PA_PROJECT_GAMEBOARD_H
