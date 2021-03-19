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

int main() {
    vector<pair<int, char>> availablePos;
    srand(time(NULL));
    GameBoard* gameBoard = new GameBoard();
    int i, sz, testCounter = 0;
    gameBoard->init();
    gameBoard->showBoard();
    // Piece* myWinner = gameBoard->table[1]['b' -'a'];
    Piece* myWinner = gameBoard->table[2]['d' - 'a' + 1];
    Piece* myQueen = gameBoard->table[1]['d' - 'a' + 1];
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
            gameBoard->init();
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
            gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1] = aux;
            
            if (testCounter < 2) {
                // cout<<"cv1"<<endl;
                availablePos = myWinner->findPositions(gameBoard);
                // cout<<"cv2"<<endl;
                sz = availablePos.size();
                // cout<<"cv3"<<endl;
                // cout<<sz<<endl;
                if(sz == 0) {
                    cout<<"resign"<<endl;
                    break;
                }
                i = rand() % sz;
                cout << "move " << myWinner->position.second << 9 - myWinner->position.first << availablePos[i].second << 9 - availablePos[i].first << endl;
                gameBoard->table[myWinner->position.first][myWinner->position.second - 'a' + 1] = NULL;
                gameBoard->table[availablePos[i].first][availablePos[i].second - 'a' + 1] = myWinner;
                myWinner->position.first = availablePos[i].first;
                myWinner->position.second = availablePos[i].second;
                testCounter++;
                gameBoard->showBoard();
            }
            else {
                gameBoard->showBoard();
                availablePos = myQueen->findPositions(gameBoard);
                sz = availablePos.size();
                for (i = 0; i < sz; i++) {
                    cout << availablePos[i].first << " " << availablePos[i].second << endl;
                }
                // cout << "cv2" << endl;
                // cout << myQueen->position.first << " " << myQueen->position.second << endl;
                if (sz == 0) {
                    cout << "resign" << endl;
                    break;
                }
                // cout << "cv1 " << sz << endl;
                i = rand() % sz;
                cout << "move " << myQueen->position.second << 9 - myQueen->position.first << availablePos[i].second << 9 - availablePos[i].first << endl;
                gameBoard->table[myQueen->position.first][myQueen->position.second - 'a' + 1] = NULL;
                gameBoard->table[availablePos[i].first][availablePos[i].second - 'a' + 1] = myQueen;
                myQueen->position.first = availablePos[i].first;
                myQueen->position.second = availablePos[i].second;
                testCounter++;
            }
           
        }
    }
    return 0;
}