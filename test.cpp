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
    GameBoard* gameBoard = new GameBoard();
    int i, sz;
    gameBoard->init();
    /*for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(gameBoard->table[i + 1][j + 1] != NULL)
                cout << gameBoard->table[i + 1][j + 1]->position.first << " " << gameBoard->table[i + 1][j + 1]->position.second << endl;
        }
    }*/
    Piece* myWinner = new Pawn(make_pair(2, 'e'), 1);
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
            cin>>command;
            cin>>command;
            cin>>command;
            cin>>command;
            cin>>command;
            cin>>command;
            cin>>command;
            cin>>command;
            cin>>command;
            cin>>command;
            //Piece* myWinner = gameBoard->table[2]['e'-'a'];
            /*
            if(instanceof<Pawn>(myWinner)) { cout << "este" << endl;}
            else {cout << "nu este" << endl;}*/
        }
        else if(strncmp(command, "accepted", strlen("accepted"))==0){
            cin >> protover;
        }
        else {
            //availablePos = myWinner->findPositions(gameBoard);
            //cout<<"cv1"<<endl;
            availablePos = myWinner->findPositions(gameBoard);
            //cout<<"cv2"<<endl;
            sz = availablePos.size();
            //cout<<"cv3"<<endl;
            cout<<sz<<endl;
            if(sz == 0)
                cout<<"resign"<<endl;
            i = rand() % sz;
            cout << "move " <<myWinner->position.second<< 9 - myWinner->position.first<<availablePos[i].second<<9 - availablePos[i].first<<endl;
            gameBoard->table[myWinner->position.first][myWinner->position.second] == NULL;
            myWinner->position.first = availablePos[i].first;
            myWinner->position.second = availablePos[i].second;
            cin>>command;
            cin>>command;
            cin>>command;
            cin>>command;
        }
    }
    return 0;
}