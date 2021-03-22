//
// Created by andrei on 11.03.2021.
//

#ifndef PA_PROJECT_PIECE_H
#define PA_PROJECT_PIECE_H
#include <vector>
#include <string>

using namespace std;

class GameBoard;
class Piece {
public:
    bool color;
    pair<int, char> position;
    Piece(pair<int, char> pos, bool color);
    virtual vector<pair<int, char>> findPositions(GameBoard* gameBoard) = 0;
    virtual string getName() = 0;
};

#endif //PA_PROJECT_PIECE_H
