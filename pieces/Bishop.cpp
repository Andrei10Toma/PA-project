#include "Bishop.hpp"
#include <vector>
#include "../GameBoard.hpp"
#include "Knight.hpp"
#include <iostream>
using namespace std;

Bishop::Bishop(pair<int, char> pos, bool color) : Piece(pos, color) {
}

vector<pair<pair<int, char>, Piece*>>Bishop::findPositions(GameBoard *gameBoard) {
    vector<pair<pair<int, char>, Piece*>> possiblePositions;
    
    
        // check superior main diagonal
        int i; char j;
        for (i = this->position.first - 1, j = this->position.second - 1; i >= 1 && j >= 'a'; i--, j--) {
            if (gameBoard->table[i][j - 'a' + 1] == NULL) {
                possiblePositions.push_back(make_pair(make_pair(i, j), this));
            }
            else if(gameBoard->table[i][j - 'a' + 1]->color != this->color)
            {
                possiblePositions.push_back(make_pair(make_pair(i, j), this));
                break;
            }
            else {
                break;
            }
        }
        // check inferior main diagonal
        for (i = this->position.first + 1, j = this->position.second + 1; i <= 8 && j <= 'h'; i++, j++) {
            if (gameBoard->table[i][j - 'a' + 1] == NULL) {
                possiblePositions.push_back(make_pair(make_pair(i, j), this));
            }
            else if(gameBoard->table[i][j - 'a' + 1]->color != this->color)
            {
                possiblePositions.push_back(make_pair(make_pair(i, j), this));
                break;
            }
            else {
                break;
            }
        }
        // check inferior second diagonal
        for (i = this->position.first + 1, j = this->position.second - 1; i <=8 && j >= 'a'; i++, j--) {
            if (gameBoard->table[i][j - 'a' + 1] == NULL) {
                possiblePositions.push_back(make_pair(make_pair(i, j), this));
            }
            else if(gameBoard->table[i][j - 'a' + 1]->color != this->color)
            {
               possiblePositions.push_back(make_pair(make_pair(i, j), this));
                break;
            }
            else {
                break;
            }
        }
        // check superior second diagonal
        for (i = this->position.first - 1, j = this->position.second + 1; i >= 1 && j <= 'h'; i--, j++) {
            if (gameBoard->table[i][j - 'a' + 1] == NULL) {
                possiblePositions.push_back(make_pair(make_pair(i, j), this));
            }
            else if(gameBoard->table[i][j - 'a' + 1]->color != this->color)
            {
                possiblePositions.push_back(make_pair(make_pair(i, j), this));
                break;
            }
            else {
                break;
            }
        }
    
    return possiblePositions;
}

string Bishop::getName() {
    return "B";
}