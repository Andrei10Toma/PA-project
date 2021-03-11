#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "GameBoard.hpp"
#include "pieces/Piece.hpp"

using namespace std;

// int main(){
//     char command[50];
//     while(1){
//         read(0, command, 50);
//         if(strncmp(command, "xboard", strlen("xboard"))) {
//             read(0, command, 50);
//             write(0, "feature sigint=0\n", 50);
//             write(0, "feature san=0\n", 50);
//             write(0, "feature myname=\"Capablanca\"\n", 50);
//         }
//         else {
//             write(0, "move e2e4\n", 50);
//             break;
//         }
//     }
// }


int main() {
    GameBoard* gameBoard = new GameBoard();
    gameBoard->init();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << gameBoard->table[i + 1][j + 1]->position.first << " " << gameBoard->table[i + 1][j + 1]->position.second << endl;
        }
    }
    char command[20];
    while (true) {
        cin >> command;
        if (strncmp(command, "xboard", strlen("xboard")) == 0) {
            cout << "feature sigint=0" << endl;
            cout << "feature san=0" << endl;
            cout << "feature myname=\"Capablanca\"" << endl;
        }
        else if (strncmp(command, "e2e4", strlen("e2e4")) == 0) {
            cout << "move e7e5" << endl;
            cout << "resign" << endl;
        }
        else if (strncmp(command, "quit", strlen("quit")) == 0) {
            break;
        }
    }
    return 0;
}