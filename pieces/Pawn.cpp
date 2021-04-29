#include "Pawn.hpp"
#include <vector>
#include "../GameBoard.hpp"
#include "Queen.hpp"
#include <iostream>
#include "Knight.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
using namespace std;

Pawn::Pawn(pair<int, char> pos, bool color) : Piece(pos, color) {
    moved_two = false;
    moveNumber = 0;
}

int Pawn::promote(GameBoard* gameBoard, vector<Piece*>& pieces, char promotionPiece) {
    unsigned int i;
    for (i = 0; i < pieces.size(); i++) {
        if (this == pieces[i]) {
            break;
        }
    }
    pieces.erase(pieces.begin() + i);
    switch (promotionPiece) {
        case 'n':
            gameBoard->table[7 * color + 1][position.second - 'a' + 1] = new Knight(make_pair(7 * color + 1, position.second), color);
            break;
        case 'q':
            gameBoard->table[7 * color + 1][position.second - 'a' + 1] = new Queen(make_pair(7 * color + 1, position.second), color);
            break;
        case 'r':
            gameBoard->table[7 * color + 1][position.second - 'a' + 1] = new Rook(make_pair(7 * color + 1, position.second), color);
            break;
        case 'b':
            gameBoard->table[7 * color + 1][position.second - 'a' + 1] = new Bishop(make_pair(7 * color + 1, position.second), color);
            break;
        default:
            break;
    }
    pieces.push_back(gameBoard->table[7 * color + 1][position.second - 'a' + 1]);
    return 1;
}

vector<pair<pair<int, char>, Piece*>> Pawn::findPositions(GameBoard* gameBoard) {
    vector<pair<pair<int, char>, Piece*>> possiblePositions;
    if (this->color == 1) {
        if (this->position.first == 2) {
            if (gameBoard->table[3][this->position.second - 'a' + 1] == NULL) {
                possiblePositions.push_back(make_pair(make_pair(3, this->position.second), this));
            }
            if (gameBoard->table[3][this->position.second - 'a' + 1] == NULL && gameBoard->table[4][this->position.second - 'a' + 1] == NULL) {
                possiblePositions.push_back(make_pair(make_pair(4, this->position.second), this));
            }
            if (position.second - 'a' > 0) {
                if (gameBoard->table[position.first + 1][position.second - 'a' ] != NULL) {
                    if (gameBoard->table[position.first + 1][position.second - 'a' ]->color != this->color)
                        possiblePositions.push_back(make_pair(make_pair(position.first + 1, position.second - 1), this));
                }
            }
            if (position.second - 'a' + 2 < 9) {
                if (gameBoard->table[position.first + 1][position.second - 'a' + 2 ] != NULL) {
                    if (gameBoard->table[position.first + 1][position.second - 'a' + 2 ]->color != this->color)
                        possiblePositions.push_back(make_pair(make_pair(position.first + 1, position.second + 1), this));
                }
            }
        }
        else {
            if (position.first + 1 < 9) {
                if (position.second - 'a' + 1 < 9) {
                    if (gameBoard->table[position.first + 1][position.second - 'a' + 1] == NULL) {
                        possiblePositions.push_back(make_pair(make_pair(position.first + 1, position.second), this));
                    }
                }
                if (position.second - 'a' > 0) {
                    if (gameBoard->table[position.first + 1][position.second - 'a' ] != NULL) {
                        if (gameBoard->table[position.first + 1][position.second - 'a' ]->color != this->color)
                            possiblePositions.push_back(make_pair(make_pair(position.first + 1, position.second - 1), this));
                    }
                }
                if (position.second - 'a' + 2 < 9) {
                    if (gameBoard->table[position.first + 1][position.second - 'a' + 2 ] != NULL) {
                        if (gameBoard->table[position.first + 1][position.second - 'a' + 2 ]->color != this->color)
                            possiblePositions.push_back(make_pair(make_pair(position.first + 1, position.second + 1), this));
                    }
                }
            }
             // en passant
            if (this->position.first == 5) {
                if (this->position.second - 'a' > 0) {
                    if (gameBoard->table[position.first][position.second - 'a'] != NULL) {
                        Piece *opponent = gameBoard->table[position.first][position.second - 'a'];
                        if(opponent->getName().compare("P") == 0 && opponent->color != this->color) {
                            if ( ((Pawn *)opponent)->moved_two == true) {
                                possiblePositions.push_back(make_pair(make_pair(position.first + 1, position.second - 1), this));
                            }
                        }
                    }
                }
                if (this->position.second - 'a' + 2 > 0) {
                    if (gameBoard->table[position.first][position.second - 'a' + 2] != NULL) {
                        Piece *opponent = gameBoard->table[position.first][position.second - 'a' + 2];
                        if(opponent->getName().compare("P") == 0 && opponent->color != this->color) {
                            if ( ((Pawn *)opponent)->moved_two == true) {
                                possiblePositions.push_back(make_pair(make_pair(position.first + 1, position.second + 1), this));
                            }
                        }
                    }
                }
                   
            }
        }
    }
    else {
        if (this->position.first == 7) {
            if (gameBoard->table[6][this->position.second - 'a' + 1] == NULL) {
                possiblePositions.push_back(make_pair(make_pair(6, this->position.second), this));
            }
            if (gameBoard->table[6][this->position.second - 'a' + 1] == NULL && gameBoard->table[5][this->position.second - 'a' + 1] == NULL) {
                possiblePositions.push_back(make_pair(make_pair(5, this->position.second), this));
            }
            if (position.second - 'a' > 0) {
                if (gameBoard->table[position.first - 1][position.second - 'a' ] != NULL) {
                    if (gameBoard->table[position.first - 1][position.second - 'a' ]->color != this->color)
                        possiblePositions.push_back(make_pair(make_pair(position.first - 1, position.second - 1), this));
                }
            }
            if (position.second - 'a' + 2 < 9) {
                if (gameBoard->table[position.first - 1][position.second - 'a' + 2 ] != NULL) {
                    if (gameBoard->table[position.first - 1][position.second - 'a' + 2 ]->color != this->color)
                        possiblePositions.push_back(make_pair(make_pair(position.first - 1, position.second + 1), this));
                }
            }
        }
        else {
            if (position.first - 1 > 0) {
                if (position.second - 'a' + 1 < 9) {
                    if (gameBoard->table[position.first - 1][position.second - 'a' + 1] == NULL) {
                        possiblePositions.push_back(make_pair(make_pair(position.first - 1, position.second), this));
                    }
                }
                if (position.second - 'a' > 0) {
                    if (gameBoard->table[position.first - 1][position.second - 'a' ] != NULL) {
                        if (gameBoard->table[position.first - 1][position.second - 'a' ]->color != this->color)
                            possiblePositions.push_back(make_pair(make_pair(position.first - 1, position.second - 1), this));
                    }
                }
                if (position.second - 'a' + 2 < 9) {
                    if (gameBoard->table[position.first - 1][position.second - 'a' + 2 ] != NULL) {
                        if (gameBoard->table[position.first - 1][position.second - 'a' + 2 ]->color != this->color)
                            possiblePositions.push_back(make_pair(make_pair(position.first - 1, position.second + 1), this));
                    }
                }
            }
            // en passant
            if (this->position.first == 4) {
                if (this->position.second - 'a' > 0) {
                        if (gameBoard->table[position.first][position.second - 'a'] != NULL) {
                            Piece *opponent = gameBoard->table[position.first][position.second - 'a'];
                            if(opponent->getName().compare("P") == 0 && opponent->color != this->color) {
                                if ( ((Pawn *)opponent)->moved_two == true) {
                                    possiblePositions.push_back(make_pair(make_pair(position.first - 1, position.second - 1), this));
                                }
                            }
                        }
                }
                if (this->position.second - 'a' + 2 > 0) {
                        if (gameBoard->table[position.first][position.second - 'a' + 2] != NULL) {
                            Piece *opponent = gameBoard->table[position.first][position.second - 'a' + 2];
                            if(opponent->getName().compare("P") == 0 && opponent->color != this->color) {
                                if ( ((Pawn *)opponent)->moved_two == true) {
                                    possiblePositions.push_back(make_pair(make_pair(position.first - 1, position.second + 1), this));
                                }
                            }
                        }
                }
                   
            }
        }
    }
    return possiblePositions;
}

string Pawn::getName() {
    return "P";
}