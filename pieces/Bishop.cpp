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
    
    if ( this -> color == 1) {
        // check superior main diagonal
        int i; char j;
        for (i = this->position.first - 1, j = this->position.second - 1; i >= 1 && j >= 'a'; i--, j--) {
            if (gameBoard->table[i][j - 'a' + 1] == NULL) {
                possiblePositions.push_back(make_pair(i, j));
            }
            else if(gameBoard->table[i][j - 'a' + 1]->color != this->color)
            {
                possiblePositions.push_back(make_pair(i, j));
                break;
            }
            else {
                break;
            }
        }
        // check inferior main diagonal
        for (i = this->position.first + 1, j = this->position.second + 1; i <= 8 && j <= 'h'; i++, j++) {
            if (gameBoard->table[i][j - 'a' + 1] == NULL) {
                possiblePositions.push_back(make_pair(i, j));
            }
            else if(gameBoard->table[i][j - 'a' + 1]->color != this->color)
            {
                possiblePositions.push_back(make_pair(i, j));
                break;
            }
            else {
                break;
            }
        }
        // check inferior second diagonal
        for (i = this->position.first + 1, j = this->position.second - 1; i <=8 && j >= 'a'; i++, j--) {
            if (gameBoard->table[i][j - 'a' + 1] == NULL) {
                possiblePositions.push_back(make_pair(i, j));
            }
            else if(gameBoard->table[i][j - 'a' + 1]->color != this->color)
            {
               possiblePositions.push_back(make_pair(i, j));
                break;
            }
            else {
                break;
            }
        }
        // check superior second diagonal
        for (i = this->position.first - 1, j = this->position.second + 1; i >= 1 && j <= 'h'; i--, j++) {
            if (gameBoard->table[i][j - 'a' + 1] == NULL) {
                possiblePositions.push_back(make_pair(i, j));
            }
            else if(gameBoard->table[i][j - 'a' + 1]->color != this->color)
            {
                possiblePositions.push_back(make_pair(i, j));
                break;
            }
            else {
                break;
            }
        }
    }
    return possiblePositions;
}

string Bishop::getName() {
    return "B";
}