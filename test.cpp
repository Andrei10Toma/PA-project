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

void remove(vector<Piece*> &pieces, Piece* piece){
    int i, sz = pieces.size();

    for(i = 0; i < sz; i++)
        if(pieces[i] == piece)
            break;
    cout << piece->color << ' ' << piece->getName() << endl;
    pieces.erase(pieces.begin() + i);
}

int main() {
    vector<pair<pair<int, char>, Piece*>> availablePos;
    vector<pair<pair<int, char>, Piece*>> pos;
    // pieces[1] -> black's pieces, pieces[0] -> white's pieces
    vector<Piece*> pieces[2];
    srand(time(NULL));
    GameBoard* gameBoard = new GameBoard();
    unsigned int i, sz, j;
    gameBoard->init(pieces[0], pieces[1]);
    gameBoard->showBoard();
    char command[20], protover[20], N;
    // mode = 1 bot plays mode = 0 watches (force)
    int mode = 1;
    // color: 1->black, 0->white
    int color;
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
            gameBoard->init(pieces[0], pieces[1]);
            mode = 1;
            color = 0;
        }
        else if(strncmp(command, "force", 5) == 0){
            mode = 0;
        }
        else if(strncmp(command, "go", 2) == 0) {
            cout<<"go!"<<endl;
            
            Piece *aux =  gameBoard->table[9 - (command[1] - '0')][command[0] - 'a' + 1];
            gameBoard->table[9 - (command[1] - '0')][command[0] - 'a' + 1] = NULL;
            Piece *captured = gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1];
            gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1] = aux;
            if(captured != NULL)
                remove(pieces[color], captured);
            cout<<color<<endl;
            mode = 1;
            sz = pieces[color].size();
            for(i = 0; i<sz; i++){
                pos = pieces[color][i]->findPositions(gameBoard);
                if (!pos.empty())
                    availablePos.insert(availablePos.end(), pos.begin(), pos.end());
            }
            
            sz = availablePos.size();
            if(sz == 0) {
                cout<<"resign"<<endl;
                break;
            }
            i = rand() % sz;
            
            cout << "move " << availablePos[i].second->position.second << 9 - availablePos[i].second->position.first 
            << availablePos[i].first.second << 9 - availablePos[i].first.first << endl;
            
            gameBoard->table[availablePos[i].second->position.first][availablePos[i].second->position.second - 'a' + 1] = NULL;
            captured = gameBoard->table[availablePos[i].first.first][availablePos[i].first.second - 'a' + 1];
            gameBoard->table[availablePos[i].first.first][availablePos[i].first.second - 'a' + 1] = availablePos[i].second;
            
            if(captured != NULL)
                remove(pieces[1-color], captured);

            availablePos[i].second->position.first = availablePos[i].first.first;
            availablePos[i].second->position.second = availablePos[i].first.second;
            availablePos.clear();
            gameBoard->showBoard();
            color = 1 - color;
        }
        else if(strncmp(command, "accepted", strlen("accepted")) == 0){
            cin >> protover;
        }
        else if (strncmp(command, "random", 6) == 0) {
            continue;
        }
        else if (strncmp(command, "white", 5) == 0) {
            //color = 0;
            continue;
        }
        else if (strncmp(command, "black", 5) == 0) {
            //color = 1;
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
            if(mode == 1) {
                color = 1 - color;
                //actualize opponent's pieces
                Piece *aux =  gameBoard->table[9 - (command[1] - '0')][command[0] - 'a' + 1];
                gameBoard->table[9 - (command[1] - '0')][command[0] - 'a' + 1] = NULL;
                Piece *captured = gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1];
                gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1] = aux;
                cout << "da1" << endl;
                aux->position.first = 9 - (command[3] - '0');
                aux->position.second = command[2];
                cout << "da2" << endl;

                if(captured != NULL)
                    remove(pieces[color], captured);
                sz = pieces[color].size();
            
                //debugging
                /*for(i = 0; i<sz; i++)
                    cout<< pieces[color][i]->getName() << ' ' << pieces[color][i]->position.first << ' '<<pieces[color][i]->position.second << endl;
                cout<< sz << endl;*/
                
                for(i = 0; i < sz; i++){
                    pos = pieces[color][i]->findPositions(gameBoard);
                    if (!pos.empty())
                        availablePos.insert(availablePos.end(), pos.begin(), pos.end());
                }
                
                sz = availablePos.size();
                if(sz == 0) {
                    cout<<"resign"<<endl;
                    break;
                }
                i = rand() % sz;
                cout << availablePos[i].second->getName() << ' ' << availablePos[i].first.first << ' ' << availablePos[i].first.second << endl;
                cout << "move " << availablePos[i].second->position.second << 9 - availablePos[i].second->position.first 
                << availablePos[i].first.second << 9 - availablePos[i].first.first << endl;
                gameBoard->table[availablePos[i].second->position.first][availablePos[i].second->position.second - 'a' + 1] = NULL;
                // gameBoard->table[availablePos[i].first.first][availablePos[i].first.second - 'a' + 1] = availablePos[i].second;
                captured = gameBoard->table[availablePos[i].first.first][availablePos[i].first.second - 'a' + 1];
                if(captured != NULL)
                    remove(pieces[1-color], captured);
                //TODO: check the segmentation fault
                // Piece *temp = availablePos[i].second;
                // int ok = 0;
                // if(availablePos[i].first.first == 8) {
                    // if(temp->getName().compare("P") == 0)
                        // ok = ((Pawn*)temp)->promoteToQueen(gameBoard, pieces[color]);
                // }
                // debug for promote
                // if (ok == 0)
                    // gameBoard->table[availablePos[i].first.first][availablePos[i].first.second - 'a' + 1] = availablePos[i].second;
                
                // if(captured != NULL)
                    // remove(pieces[1-color], captured);

                availablePos[i].second->position.first = availablePos[i].first.first;
                availablePos[i].second->position.second = availablePos[i].first.second;
                Piece *temp = availablePos[i].second;
                int ok = 0;
                if(availablePos[i].first.first == 7 * color + 1) {
                    if(temp->getName().compare("P") == 0)
                        ok = ((Pawn*)temp)->promoteToQueen(gameBoard, pieces[color]);
                }
                if (ok == 0)
                    gameBoard->table[availablePos[i].first.first][availablePos[i].first.second - 'a' + 1] = availablePos[i].second;
                availablePos.clear();
                cout << "WP: ";
                for (j = 0; j < pieces[0].size(); j++) {
                    cout << pieces[0][j]->getName() << " ";
                }
                cout << endl;
                cout << "BP: ";
                for (j = 0; j < pieces[1].size(); j++) {
                    cout << pieces[1][j]->getName() << " ";
                }
                cout << endl;
                color = 1 - color;
                gameBoard->showBoard();
            }
            else {
                int ok;
                Piece *aux =  gameBoard->table[9 - (command[1] - '0')][command[0] - 'a' + 1];
                gameBoard->table[9 - (command[1] - '0')][command[0] - 'a' + 1] = NULL;
                Piece *captured = gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1];
                gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1] = aux;
                aux->position.first = 9 - (command[3] - '0');
                aux->position.second = command[2];
                if(captured != NULL) {
                    if(captured->color == 1)
                        remove(pieces[1], captured);
                    else
                        remove(pieces[0], captured);
                }
                Piece *temp = gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1];

                // cout << "color = " << color << endl;
                if (temp->position.first == 7 * color + 1) {
                    if (temp->getName().compare("P") == 0) {
                        ok = ((Pawn *)temp)->promoteToQueen(gameBoard, pieces[color]);
                    }
                }
                // color = 1 - color;
                // debug for promote
                cout << "WP: ";
                for (j = 0; j < pieces[0].size(); j++) {
                    cout << pieces[0][j]->getName() << " ";
                }
                cout << endl;
                cout << "BP: ";
                for (j = 0; j < pieces[1].size(); j++) {
                    cout << pieces[1][j]->getName() << " ";
                }
                cout << endl;
                color = 1 - color;

                gameBoard->showBoard();
            }
        }
    }
    return 0;
}