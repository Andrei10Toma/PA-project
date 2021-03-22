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

template<typename Base, typename T>
inline bool instanceof(const T*) {
    return std::is_base_of<Base, T>::value;
}

void remove(vector<Piece*> pieces, Piece* piece){
    int i, sz = pieces.size();
    for(i = 0; i < sz; i++)
        if(pieces[i] == piece)
            break;
    pieces.erase(pieces.begin() + i);
}

int main() {
    vector<pair<pair<int, char>, Piece*>> availablePos;
    vector<pair<pair<int, char>, Piece*>> pos;
    vector<Piece*> white;
    vector<Piece*> black;
    srand(time(NULL));
    GameBoard* gameBoard = new GameBoard();
    int i, sz;
    gameBoard->init(white, black);
    gameBoard->showBoard();
    char command[20], protover[20], N;
    while (true) {
        cin >> command;
        if (strncmp(command, "xboard", strlen("xboard")) == 0) {
            cin >> protover >> N;
            cout << "feature sigint=0" << endl;
            cout << "feature san=0" << endl;
            cout << "feature myname=\"Capablanca\"" << endl;
        }
        else if (strncmp(command, "quit", strlen("quit")) == 0) {
            break;
        }
        else if(strncmp(command, "new", 3)==0){
            gameBoard->init(white, black);
        }
        else if(strncmp(command, "accepted", strlen("accepted")) == 0){
            cin >> protover;
        }
        else if (strncmp(command, "random", 6) == 0) {
            continue;
        }
        else if (strncmp(command, "level", 5) == 0) {
            cin >> command;
            cin >> command;
            cin >> command;
        }
        else if (strncmp(command, "post", 4) == 0) {
            continue;
        }
        else if (strncmp(command, "hard", 4) == 0) {
            continue;
        }
        else if (strncmp(command, "time", 4) == 0) {
            cin >> command;
        }
        else if (strncmp(command, "otim", 4) == 0) {
            cin >> command;
        }
        else {
             //actualize opponent's pieces
            Piece *aux =  gameBoard->table[9 - (command[1] - '0')][command[0] - 'a' + 1];
            gameBoard->table[9 - (command[1] - '0')][command[0] - 'a' + 1] = NULL;
            Piece *captured = gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1];
            gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1] = aux;
            if(captured != NULL)
                remove(black, captured);
            
            sz = black.size();
            for(i = 0; i<sz; i++){
                pos = black[i]->findPositions(gameBoard);
                availablePos.insert(availablePos.end(), pos.begin(), pos.end());
            }
            sz = availablePos.size();
            if(sz == 0) {
                cout<<"resign"<<endl;
                break;
            }
            i = rand() % sz;
            cout << availablePos[i].second->getName() << ' '<< availablePos[i].first.first << ' ' << availablePos[i].first.second << endl;
            cout << "move " << availablePos[i].second->position.second << 9 - availablePos[i].second->position.first 
            << availablePos[i].first.second << 9 - availablePos[i].first.first << endl;
            gameBoard->table[availablePos[i].second->position.first][availablePos[i].second->position.second - 'a' + 1] = NULL;
            captured = gameBoard->table[availablePos[i].first.first][availablePos[i].first.second - 'a' + 1] ;
            gameBoard->table[availablePos[i].first.first][availablePos[i].first.second - 'a' + 1] = availablePos[i].second;
            if(captured != NULL)
                remove(white, captured);
            availablePos[i].second->position.first = availablePos[i].first.first;
            availablePos[i].second->position.second = availablePos[i].first.second;
            gameBoard->showBoard();
        }
    }
    return 0;
}