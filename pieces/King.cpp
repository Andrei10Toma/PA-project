#include "King.hpp"
#include <vector>
#include "../GameBoard.hpp"
#include <iostream>
#include "Rook.hpp"
using namespace std;

King::King(pair<int, char> pos, bool color) : Piece(pos, color) {
    hasMoved = false;
}

vector<pair<pair<int, char>, Piece*>> King::findPositions(GameBoard* gameBoard) {
    vector<pair<pair<int, char>, Piece*>> possiblePositions;
    int vx[] = {0, 0, -1, -1, -1, 1, 1, 1};
    int vy[] = {-1, 1, -1, 0, 1, -1, 0, 1};
    int i;
    for (i = 0; i < 8; i++) {
        if (inTable(this->position.first + vx[i], 
            this->position.second + vy[i], gameBoard, this)) {
                possiblePositions.push_back(make_pair(
                        make_pair(this->position.first + vx[i], 
                        this->position.second + vy[i]), this));
        }
    }
    if(this->hasMoved == false){
        if(this->color == 1){
            //Castle king-side black
            // The rook is where he should be
            if(gameBoard->table[1][8] != NULL && gameBoard->table[1][8]->color == 1 && 
            gameBoard->table[1][8]->getName().compare("R") == 0){
                // The rook hasn't moved and there is no piece in between
                if(((Rook*)gameBoard->table[1][8])->hasMoved == false && 
                gameBoard->table[1][6] == NULL && gameBoard->table[1][7] == NULL){
                    possiblePositions.push_back(make_pair(make_pair(this->position.first,
                     this->position.second + 2), this));
                }
            }
            // Castle queen-side black
            if(gameBoard->table[1][1] != NULL && gameBoard->table[1][1]->color == 1 &&
             gameBoard->table[1][1]->getName().compare("R") == 0){
                // The rook hasn't moved and there is no piece in between
                if(((Rook*)gameBoard->table[1][1])->hasMoved == false && 
                gameBoard->table[1][2] == NULL && gameBoard->table[1][3] == NULL 
                && gameBoard->table[1][4] == NULL){
                    possiblePositions.push_back(make_pair(make_pair(this->position.first,
                     this->position.second - 2), this));
                }
            }
        }
        else{
            //Castle king-side black
            // The rook is where he should be
            if(gameBoard->table[8][8] != NULL && gameBoard->table[8][8]->color == 0 && 
            gameBoard->table[8][8]->getName().compare("R") == 0){
                // The rook hasn't moved and there is no piece in between
                if(((Rook*)gameBoard->table[8][8])->hasMoved == false && 
                gameBoard->table[8][6] == NULL && gameBoard->table[8][7] == NULL){
                    possiblePositions.push_back(make_pair(make_pair(this->position.first,
                     this->position.second + 2), this));
                }
            }
            // Castle queen-side black
            if(gameBoard->table[8][1] != NULL && gameBoard->table[8][1]->color == 0 &&
             gameBoard->table[8][1]->getName().compare("R") == 0){
                // The rook hasn't moved and there is no piece in between
                if(((Rook*)gameBoard->table[8][1])->hasMoved == false && 
                gameBoard->table[8][2] == NULL && gameBoard->table[8][3] == NULL 
                && gameBoard->table[8][4] == NULL){
                    possiblePositions.push_back(make_pair(make_pair(this->position.first,
                     this->position.second - 2), this));
                }
            }
        }
    }
    return possiblePositions;
}

string King::getName() {
    return "K";
}