#include "Bishop.hpp"
#include <vector>
#include "../GameBoard.hpp"
#include "Knight.hpp"
#include <iostream>
using namespace std;

Bishop::Bishop(pair<int, char> pos, bool color) : Piece(pos, color) {
}

bool inTableBishop(int x, char y, GameBoard * gameBoard){
    cout << x << ' ' << y << endl;
    if(x >= 9 || x <= 0 || y < 'a' || y > 'h')
        return false;
    if(gameBoard->table[x][y - 'a' + 1] != NULL && gameBoard->table[x][y - 'a' + 1]->color == 1)
        return false;
    return true;
}
vector<pair<int, char>>Bishop::findPositions(GameBoard *gameBoard) {
    vector<pair<int, char>> possiblePositions;
    int currentLine = this->position.first;
    char currentColumn = this->position.second;
    // right - up
    int line = currentLine + 1;
    char col = currentColumn + 1;
    while(inTableBishop(line, col, gameBoard)) {
        possiblePositions.push_back(make_pair(line, col - 'a' + 1));
        line++;
        col++;
    }
    // left - down
    line = currentLine - 1;
    col = currentColumn - 1;
     while(inTableBishop(line, col, gameBoard)) {
        possiblePositions.push_back(make_pair(line, col - 'a' + 1));
        line --;
        col--;
    }
    // left - up
    line = currentLine + 1;
    col = currentColumn - 1;
    while(inTableBishop(line, col, gameBoard)) {
        possiblePositions.push_back(make_pair(line, col - 'a' + 1));
        line++;
        col--;
    }
    // right - down
    line = currentLine - 1;
    col = currentColumn + 1;
    while(inTableBishop(line, col, gameBoard)) {
        possiblePositions.push_back(make_pair(line, col - 'a' + 1));
        line--;
        col++;
    }
    return possiblePositions;
}