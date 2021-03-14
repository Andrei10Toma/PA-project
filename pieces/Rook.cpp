#include "Rook.hpp"
#include <vector>
#include "../GameBoard.hpp"
#include <iostream>
using namespace std;

Rook::Rook(pair<int, char> pos, bool color) : Piece(pos, color) {
}

vector<pair<int, char>> Rook::findPositions(GameBoard* gameBoard) {
    vector<pair<int, char>> possiblePositions;
    int currentLine = this->position.first;
    char currentColumn = this->position.second;
    if (this->color == 1) {
        int line;
        if(currentLine < 8) {
            for (line = currentLine + 1; line < 9; line++) {
                if (gameBoard->table[line][currentColumn - 'a' + 1] == NULL) {
                  possiblePositions.push_back(make_pair(line, currentColumn));
                }
                else break;
            }
        }
        if (currentLine > 1) {
            for (line = currentLine - 1; line > 0; line--) {
                if (gameBoard->table[line][currentColumn - 'a' + 1] == NULL) {
                  possiblePositions.push_back(make_pair(line, currentColumn));
                }
                else break;
            }
        }
        char col;
        if (currentColumn < 'h') {
            for (col = currentColumn + 1; col < 'i'; col++) {
                if (gameBoard->table[currentLine][col - 'a' + 1] == NULL) {
                    possiblePositions.push_back(make_pair(currentLine, col));
                }
                else break;
            }
        }
        if (currentColumn > 'a') {
            for (col = currentColumn - 1; col >= 'a'; col--) {
                if (gameBoard->table[currentLine][col - 'a' + 1] == NULL) {
                    possiblePositions.push_back(make_pair(currentLine, col));
                }
                else break;
            }
        }   
    }
    return possiblePositions;
}