#include "Rook.hpp"
#include <vector>
#include "../GameBoard.hpp"
#include <iostream>
using namespace std;

Rook::Rook(pair<int, char> pos, bool color) : Piece(pos, color) {
    hasMoved = false;
}

vector<pair<pair<int, char>, Piece*>> Rook::findPositions(GameBoard* gameBoard) {
    vector<pair<pair<int, char>, Piece*>> possiblePositions;
    int currentLine = this->position.first;
    char currentColumn = this->position.second;
    
        int line;
        if(currentLine < 8) {
            for (line = currentLine + 1; line < 9; line++) {
                if (gameBoard->table[line][currentColumn - 'a' + 1] == NULL) {
                  possiblePositions.push_back(make_pair(make_pair(line, currentColumn), this));
                }
                else if (gameBoard->table[line][currentColumn - 'a' + 1]->color != this->color) {
                    possiblePositions.push_back(make_pair(make_pair(line, currentColumn), this));
                    break;
                }
                else break;
            }
        }
        if (currentLine > 1) {
            for (line = currentLine - 1; line > 0; line--) {
                if (gameBoard->table[line][currentColumn - 'a' + 1] == NULL) {
                  possiblePositions.push_back(make_pair(make_pair(line, currentColumn), this));
                }
                else if (gameBoard->table[line][currentColumn - 'a' + 1]->color != this->color) {
                    possiblePositions.push_back(make_pair(make_pair(line, currentColumn), this));
                    break;
                }
                else break;
            }
        }
        char col;
        if (currentColumn < 'h') {
            for (col = currentColumn + 1; col < 'i'; col++) {
                if (gameBoard->table[currentLine][col - 'a' + 1] == NULL) {
                    possiblePositions.push_back(make_pair(make_pair(currentLine, col), this));
                }
                else if (gameBoard->table[currentLine][col - 'a' + 1]->color != this->color) {
                    possiblePositions.push_back(make_pair(make_pair(currentLine, col), this));
                    break;
                }
                else break;
            }
        }
        if (currentColumn > 'a') {
            for (col = currentColumn - 1; col >= 'a'; col--) {
                if (gameBoard->table[currentLine][col - 'a' + 1] == NULL) {
                    possiblePositions.push_back(make_pair(make_pair(currentLine, col), this));
                }
                else if (gameBoard->table[currentLine][col - 'a' + 1]->color != this->color) {
                    possiblePositions.push_back(make_pair(make_pair(currentLine, col), this));
                    break;
                }
                else break;
            }
        }   
    return possiblePositions;
}


string Rook::getName() {
    return "R";
}