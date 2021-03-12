//
// Created by andrei on 11.03.2021.
//

#ifndef PA_PROJECT_PIECE_H
#define PA_PROJECT_PIECE_H
#include <vector>
#include "../GameBoard.hpp"

using namespace std;

class Piece {
public:
    bool color;
    pair<int, char> position;
    Piece(pair<int, char> pos, bool color);
    virtual vector<pair<int, char>> findPositions(GameBoard gameBoard);
};


#endif //PA_PROJECT_PIECE_H
