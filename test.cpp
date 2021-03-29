#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "GameBoard.hpp"
#include "pieces/Piece.hpp"
#include "pieces/Pawn.hpp"

using namespace std;

void remove(vector<Piece*> &pieces, Piece* piece){
    int i, sz = pieces.size();
    for(i = 0; i < sz; i++)
        if(pieces[i] == piece)
            break;
    //Remove piece if found
    if(i != sz)
        pieces.erase(pieces.begin() + i);
}

void updateOpponentPieces(GameBoard* gameBoard, string command, vector<Piece*> pieces[], int color, vector<Piece*>& theChosenOnes) {
    // Actualize table
    Piece *aux =  gameBoard->table[9 - (command[1] - '0')][command[0] - 'a' + 1];
    gameBoard->table[9 - (command[1] - '0')][command[0] - 'a' + 1] = NULL;
    Piece *captured = gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1];
    gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1] = aux;
    aux->position.first = 9 - (command[3] - '0');
    aux->position.second = command[2];

    // Remove pawn if captured
    if(captured != NULL) {
        for (int i = 0; i < 2; i++) {
            if (captured == theChosenOnes[i])
                theChosenOnes[i] = NULL;
        }
        remove(pieces[captured->color], captured);
    }
    Piece *temp = gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1];

    // Promote
    if (temp->position.first == 7 * color + 1) {
        if (temp->getName().compare("P") == 0) {
            ((Pawn *)temp)->promoteToQueen(gameBoard, pieces[color], theChosenOnes[color]);
        }
    }
}

int computeNextMove(GameBoard *gameBoard, vector<Piece*> pieces[], int color, Piece* &theChosenOne) {
    int sz = pieces[color].size(), i, ok = 0;
    vector<pair<pair<int, char>, Piece*>> availablePos;
    vector<pair<pair<int, char>, Piece*>> pos;
    Piece *captured, *temp;
    
    if (theChosenOne == NULL) {
        return -1;
    }
    availablePos = theChosenOne->findPositions(gameBoard);
    
    sz = availablePos.size();
    // No moves => resign
    if(sz == 0) {
        return -1;
    }

    // Print the move
    i = rand() % sz;
    cout << "move " << availablePos[i].second->position.second << 9 - availablePos[i].second->position.first 
    << availablePos[i].first.second << 9 - availablePos[i].first.first << endl;

    // Actualize position on table
    gameBoard->table[availablePos[i].second->position.first][availablePos[i].second->position.second - 'a' + 1] = NULL;
    captured = gameBoard->table[availablePos[i].first.first][availablePos[i].first.second - 'a' + 1];

    if(captured != NULL)
        remove(pieces[1-color], captured);

    // Actualize moved piece position
    availablePos[i].second->position.first = availablePos[i].first.first;
    availablePos[i].second->position.second = availablePos[i].first.second;

    // Promote
    temp = availablePos[i].second;
    if(availablePos[i].first.first == 7 * color + 1) {
        if(temp->getName().compare("P") == 0)
            ok = ((Pawn*)temp)->promoteToQueen(gameBoard, pieces[color], theChosenOne);
    }

    if (ok == 0)
        gameBoard->table[availablePos[i].first.first][availablePos[i].first.second - 'a' + 1] = availablePos[i].second;
    availablePos.clear();
    return 1;
}

int main() {
    vector<pair<pair<int, char>, Piece*>> availablePos;
    vector<pair<pair<int, char>, Piece*>> pos;
    // pieces[0] -> white's pieces; pieces[1] -> black's pieces
    // theChosenOnes[0] -> white pawn; theChosenOne[1] -> black pawn
    vector<Piece*> pieces[2], theChosenOnes;
    GameBoard* gameBoard = new GameBoard();
    char command[20], protover[20], N;
    // mode: 1 -> bot plays, 0 -> force
    int mode = 1;
    // color: 1 -> black, 0 -> white
    int color = 0;

    srand(time(NULL));
    
    while (true) {
        cin >> command;
        if (strncmp(command, "xboard", 6) == 0) {
            cin >> protover >> N;
            cout << "feature sigint=0" << endl;
            cout << "feature san=0" << endl;
            cout << "feature myname=\"Capablanca\"" << endl;
        }
        else if (strncmp(command, "quit", 4) == 0) {
            break;
        }
        else if (strncmp(command, "result", 6) == 0) {
            cin >> protover;
            cin >> protover;
            cin >> protover;
        }
        else if(strncmp(command, "new", 3)==0) {
            theChosenOnes.clear();
            gameBoard->init(pieces[0], pieces[1]);
            theChosenOnes.push_back(gameBoard->table[7][2]);
            theChosenOnes.push_back(gameBoard->table[2][2]);
            mode = 1;
            color = 0;
            gameBoard->showBoard();
        }
        else if(strncmp(command, "force", 5) == 0){
            mode = 0;
        }
        else if(strncmp(command, "go", 2) == 0) {
            if (computeNextMove(gameBoard, pieces, color, theChosenOnes[color]) == -1) {
                cout << "resign" << endl;
            }
            color = 1 - color;
            mode = 1;
            gameBoard->showBoard();
        }
        else if(strncmp(command, "accepted", strlen("accepted")) == 0){
            cin >> protover;
        }
        else if (strncmp(command, "level", 5) == 0) {
            cin >> command;
            cin >> command;
            cin >> command;
        }
        else if (strncmp(command, "post", 4) == 0 || strncmp(command, "hard", 4) == 0 
                || strncmp(command, "computer", 8) == 0 || strncmp(command, "black", 5) == 0
                || strncmp(command, "white", 5) == 0 || strncmp(command, "random", 6) == 0) {
            continue;
        }
        else if (strncmp(command, "time", 4) == 0 || strncmp(command, "otim", 4) == 0) {
            cin >> command;
        }
        else {
            if(mode == 1) {
                color = 1 - color;
                updateOpponentPieces(gameBoard, command, pieces, color, theChosenOnes);
                if (computeNextMove(gameBoard, pieces, color, theChosenOnes[color]) == -1) {
                    cout << "resign" << endl;
                }
                color = 1 - color;
                gameBoard->showBoard();

            }
            else {
                updateOpponentPieces(gameBoard, command, pieces, color, theChosenOnes);
                color = 1 - color;
                gameBoard->showBoard();
            }
        }
    }
    return 0;
}