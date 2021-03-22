#include "Knight.hpp"  
#include <vector>
#include "../GameBoard.hpp"
#include <iostream>
using namespace std;

Knight::Knight(pair<int, char> pos, bool color) : Piece(pos, color) {
}

bool inTable(int x, char y, GameBoard * gameBoard){
    cout << x << ' ' << y << endl;
    if(x >= 9 || x <= 0 || y < 'a' || y > 'h')
        return false;
    if(gameBoard->table[x][y - 'a' + 1] != NULL && gameBoard->table[x][y - 'a' + 1]->color == 1)
        return false;
    return true;
}

vector<pair<int, char>> Knight::findPositions(GameBoard* gameBoard) {
    vector<pair<int, char>> possiblePositions;
    int vx[] = {1, 2, 2, 1, -1, -2, -2, -1};
    int vy[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int i;
    for(i = 0; i < 8; i++)
        if(inTable(position.first + vx[i], position.second + vy[i], gameBoard))
            possiblePositions.push_back(make_pair(position.first + vx[i], position.second + vy[i]));
    return possiblePositions;
}