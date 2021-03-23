#include "Queen.hpp"
#include <vector>
#include "../GameBoard.hpp"
#include <iostream>
using namespace std;  
	
Queen::Queen(pair<int, char> pos, bool color) : Piece(pos, color){
}

bool inTableQueen(int x, char y, GameBoard* gameBoard) {
    if (x >= 9 || x <= 0 || y < 'a' || y > 'h') {
        return false;
    }
    if (gameBoard->table[x][y - 'a' + 1] != NULL && gameBoard->table[x][y - 'a' + 1]->color == 1) {
        return false;
    }
    return true;
}

vector<pair<pair<int, char>, Piece*>> Queen::findPositions(GameBoard* gameBoard) {
    vector<pair<pair<int, char>, Piece*>> possiblePositions;
    
    // check upper line
    for (int i = this->position.first - 1; i >= 1; i--) {
        if (gameBoard->table[i][this->position.second - 'a' + 1] == NULL) {
            possiblePositions.push_back(make_pair(make_pair(i, this->position.second), this));
        }
        else if(gameBoard->table[i][this->position.second - 'a' + 1]->color != this->color)
        {
            possiblePositions.push_back(make_pair(make_pair(i, this->position.second), this));
            break;
        }
        else {
            break;
        }
    }
    // check lower line
    for (int i = this->position.first + 1; i <= 8; i++) {
        if (gameBoard->table[i][this->position.second - 'a' + 1] == NULL) {
            possiblePositions.push_back(make_pair(make_pair(i, this->position.second), this));
        }
        else if(gameBoard->table[i][this->position.second - 'a' + 1]->color != this->color)
        {
            possiblePositions.push_back(make_pair(make_pair(i, this->position.second), this));
            break;
        }
        else {
            break;
        }
    }
    // check left line
    for (int i = this->position.second + 1; i <= 'h'; i++) {
        if (gameBoard->table[this->position.first][i - 'a' + 1] == NULL) {
            possiblePositions.push_back(make_pair(make_pair(this->position.first, i), this));
        }
        else if(gameBoard->table[this->position.first][i - 'a' + 1]->color != this->color)
        {
            possiblePositions.push_back(make_pair(make_pair(this->position.first, i), this));
            break;
        }
        else {
            break;
        }
    }
    // check right line
    for (int i = this->position.second - 1; i >= 'a'; i--) {
        if (gameBoard->table[this->position.first][i - 'a' + 1] == NULL) {
            possiblePositions.push_back(make_pair(make_pair(this->position.first, i), this));
        }
        else if(gameBoard->table[this->position.first][i - 'a' + 1]->color != this->color)
        {
            possiblePositions.push_back(make_pair(make_pair(this->position.first, i), this));
            break;
        }
        else {
            break;
        }
    }
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

string Queen::getName() {
    return "Q";
} 