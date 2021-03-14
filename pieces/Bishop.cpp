#include "Bishop.hpp"
#include <vector>
#include "../GameBoard.hpp"
#include "Knight.hpp"
#include <iostream>
using namespace std;

Bishop::Bishop(pair<int, char> pos, bool color) : Piece(pos, color) {
}

vector<pair<int, char>>Bishop::findPositions(GameBoard *gameBoard) {
    vector<pair<int, char>> possiblePositions;
    int currentLine = this->position.first;
    char currentColumn = this->position.second;
    
    if ( this -> color == 1) {
        // right - up
        int line = currentLine + 1;
        char col = currentColumn + 1;
        while(inTable(line, col, gameBoard)) {
            possiblePositions.push_back(make_pair(line, col - 'a' + 1));
            line++;
            col++;
        }
        // left - down
        line = currentLine - 1;
        col = currentColumn - 1;
        while(inTable(line, col, gameBoard)) {
            possiblePositions.push_back(make_pair(line, col - 'a' + 1));
            line --;
            col--;
        }
        // left - up
        line = currentLine + 1;
        col = currentColumn - 1;
        while(inTable(line, col, gameBoard)) {
            possiblePositions.push_back(make_pair(line, col - 'a' + 1));
            line++;
            col--;
        }
        // right - down
        line = currentLine - 1;
        col = currentColumn + 1;
        while(inTable(line, col, gameBoard)) {
            possiblePositions.push_back(make_pair(line, col - 'a' + 1));
            line--;
            col++;
        }
    }
    return possiblePositions;
}