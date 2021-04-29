#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "GameBoard.hpp"
#include "pieces/Piece.hpp"
#include "pieces/Rook.hpp"
#include "pieces/King.hpp"
#include "pieces/Rook.hpp"
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

void removeMove(Piece *piece, pair<int, char> move, GameBoard *gameBoard, vector<Piece*> pieces[], int color, Piece *&captured){
    //Castle king side
    if(piece->getName().compare("K") == 0 && move.second - piece->position.second == 2){
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][piece->position.second - 'a' + 2];
        gameBoard->table[piece->position.first][piece->position.second - 'a' + 2] = NULL;
        gameBoard->table[piece->position.first][8] = rook;
    }
    //Castle queen side
    if(piece->getName().compare("K") == 0 && move.second - piece->position.second == -2){
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][piece->position.second - 'a'];
        gameBoard->table[piece->position.first][piece->position.second - 'a'] = NULL;
        gameBoard->table[piece->position.first][1] = rook;
    }
    if(captured != NULL)
        gameBoard->table[captured->position.first][captured->position.second - 'a' + 1] = captured;
    else
        gameBoard->table[move.first][move.second - 'a' + 1] = captured;
    gameBoard->table[piece->position.first][piece->position.second - 'a' + 1] = piece;
    if(captured != NULL)
        pieces[color].push_back(captured);
}

int tryMove(Piece *piece, pair<int, char> move, GameBoard *gameBoard, vector<Piece*> pieces[], int color, Piece *&captured){
    //Castle king side
    int castle = 0;
    if(piece->getName().compare("K") == 0 && move.second - piece->position.second == 2){
        castle = 1;
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][8];
        gameBoard->table[piece->position.first][piece->position.second - 'a' + 2] = rook;
        gameBoard->table[piece->position.first][8] = NULL;
    }
    //Castle queen side
    if(piece->getName().compare("K") == 0 && move.second - piece->position.second == -2){
        castle = 2;
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][1];
        gameBoard->table[piece->position.first][piece->position.second -'a'] = rook;
        gameBoard->table[piece->position.first][1] = NULL;
    }
    if(piece->getName().compare("P") == 0 && abs(move.second - piece->position.second) == 1 
    && abs(move.first - piece->position.first) == 1 && gameBoard->table[move.first][move.second - 'a' + 1] == NULL){
        captured = gameBoard->table[piece->position.first][move.second - 'a' + 1];
        gameBoard->table[piece->position.first][move.second - 'a' + 1] = NULL;
    }
    else
        captured = gameBoard->table[move.first][move.second - 'a' + 1];
    
    gameBoard->table[piece->position.first][piece->position.second - 'a' + 1] = NULL;
    gameBoard->table[move.first][move.second - 'a' + 1] = piece;
    //cout << piece->getName() << ' ' << move.second << ' ' << move.first << ' ' << piece->position.second << ' ' << piece->position.first << endl; 
    if(captured != NULL)
        remove(pieces[color], captured);

    //cout << "got here try move" << endl;
    vector<pair<pair<int, char>, Piece*>> moves;
    vector<pair<pair<int, char>, Piece*>> aux;
    int sz = pieces[color].size(), i;

    for(i = 0; i < sz; i++){
        aux = pieces[color][i]->findPositions(gameBoard);
        moves.insert(moves.end(), aux.begin(), aux.end());
    }

    int ok = 1;
    sz = moves.size();
    for(i = 0; i < sz && ok; i++){
        Piece *p = gameBoard->table[moves[i].first.first][moves[i].first.second - 'a' + 1];
        // King side castle
        if(castle == 1){
            // in check
            if(moves[i].first.first == piece->position.first 
            && moves[i].first.second == piece->position.second)
                ok = 0;
            // going through check
            if(moves[i].first.first == piece->position.first 
            && moves[i].first.second == piece->position.second + 1)
                ok = 0;
        }
        // Quuen side castle
        if(castle == 2){
            // in check
            if(moves[i].first.first == piece->position.first 
            && moves[i].first.second == piece->position.second)
                ok = 0;
            // going through check
            if(moves[i].first.first == piece->position.first 
            && moves[i].first.second == piece->position.second - 1)
                ok = 0;
        }
        // King in check
        if(p != NULL && p->color == 1 - color && p->getName().compare("K") == 0)
            ok = 0;
    }
    

    return ok;
}

vector<pair<pair<int, char>, Piece*>> computePositions(GameBoard *gameBoard, vector<Piece*> pieces[], int color){
    vector<pair<pair<int, char>, Piece*>> moves;
    vector<pair<pair<int, char>, Piece*>> goodMoves;
    Piece *captured;
    int sz = pieces[color].size(), sz2, i, j;
    for(i = 0; i < sz; i++) {
        moves = pieces[color][i]->findPositions(gameBoard);
        //cout << "got here comp pos" << endl;
        sz2 = moves.size();
        for(j = 0; j < sz2; j++) {
            if(tryMove(pieces[color][i], moves[j].first, gameBoard, pieces, 1 - color, captured))
                goodMoves.push_back(moves[j]);
            removeMove(pieces[color][i], moves[j].first, gameBoard, pieces, 1 - color, captured);
        }
    }
    return goodMoves;
}

void updateOpponentPieces(GameBoard* gameBoard, string command, vector<Piece*> pieces[], int color, Piece *&pieceEP) {
    // Update table
    Piece *aux =  gameBoard->table[9 - (command[1] - '0')][command[0] - 'a' + 1];
    Piece *piece = aux;
    Piece *captured = NULL;
    if(piece->getName().compare("K") == 0)
        ((King *)piece)->hasMoved = true;

    if(piece->getName().compare("R") == 0)
        ((Rook *)piece)->hasMoved = true;
    // CASTLE
    if(piece->getName().compare("K") == 0 && command[2] - piece->position.second == 2){
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][8];
        gameBoard->table[piece->position.first][piece->position.second - 'a' + 2] = rook;
        gameBoard->table[piece->position.first][8] = NULL;
        rook->position.second = piece->position.second + 1;
    }
    //Castle queen side
    if(piece->getName().compare("K") == 0 && command[2] - piece->position.second == -2){
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][1];
        gameBoard->table[piece->position.first][piece->position.second -'a'] = rook;
        gameBoard->table[piece->position.first][1] = NULL;
        rook->position.second = piece->position.second - 1;
    }
    // En passant
    if(piece->getName().compare("P") == 0 && abs(command[3] - command[1]) == 2) {
        pieceEP = piece;
        ((Pawn *)piece)->moved_two = true;
    }
    // En passant capture
    if (piece->getName().compare("P") == 0 && abs(command[3] - command[1]) == 1
    && abs(command[2] - command[0]) == 1) {
        captured = gameBoard->table[9 - (command[1] - '0')][command[2] - 'a' + 1];
        gameBoard->table[9 - (command[1] - '0')][command[2] - 'a' + 1] = NULL;
    } else {
        captured = gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1];
    }
    gameBoard->table[9 - (command[1] - '0')][command[0] - 'a' + 1] = NULL;
    gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1] = aux;
    if (captured != NULL) cout << captured->getName() << " " << captured->position.first << " " << captured->position.second << endl;
    aux->position.first = 9 - (command[3] - '0');
    aux->position.second = command[2];

    // Remove if captured
    if(captured != NULL) {
        remove(pieces[captured->color], captured);
    }
    Piece *temp = gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1];

    // Promote
    if (temp->position.first == 7 * (1 - color) + 1) {
        if (temp->getName().compare("P") == 0) {
            ((Pawn *)temp)->promote(gameBoard, pieces[1 - color], command[4]); 
        }
    }
}

int computeNextMove(GameBoard *gameBoard, vector<Piece*> pieces[], int color) {
    int sz = pieces[color].size(), i, ok = 0;
    vector<pair<pair<int, char>, Piece*>> availablePos;
    vector<pair<pair<int, char>, Piece*>> pos;
    Piece *captured, *temp;
    vector<char> possiblePromotes = {'q', 'r', 'b', 'n'};
    char chosenPromotion = 'q';
    
    availablePos = computePositions(gameBoard, pieces, color);
    
    sz = availablePos.size();
    // No moves => resign
    if(sz == 0) {
        return -1;
    }
    int move = -1, castle = 0, enPassant = 0;
    for(i = 0; i < sz; i++){
        // castle
        if(availablePos[i].second->getName().compare("K") == 0){
            if(availablePos[i].second->position.second - availablePos[i].first.second == 2){
                move = i;
                castle = 2;
                enPassant = 0;
                break;
            }
            if(availablePos[i].second->position.second - availablePos[i].first.second == -2){
                move = i;
                castle = 1;
                enPassant = 0;
                break;
            }
        }
        if (availablePos[i].second->getName().compare("P") == 0) {
            if (availablePos[i].second->position.second != availablePos[i].first.second 
            && gameBoard->table[availablePos[i].first.first][availablePos[i].first.second - 'a' + 1] == NULL) {
                cout << "ONE EN PASSANT" << endl;
                enPassant = 1;
                move = i;
            }
        }
    }
    // Print the move
    if(move == -1)
        i = rand() % sz;
    else
        i = move;
    if (availablePos[i].first.first == 7 * color + 1 && availablePos[i].second->getName().compare("P") == 0) {
        chosenPromotion = possiblePromotes[rand() % 4];
        cout << "move " << availablePos[i].second->position.second << 9 - availablePos[i].second->position.first 
        << availablePos[i].first.second << 9 - availablePos[i].first.first << chosenPromotion << endl;
    } else {
        cout << "move " << availablePos[i].second->position.second << 9 - availablePos[i].second->position.first 
        << availablePos[i].first.second << 9 - availablePos[i].first.first << endl;
    }

    // Actualize position on table
    if(availablePos[i].second->getName().compare("K") == 0){
        ((King *)availablePos[i].second)->hasMoved = true;
    }
    if(availablePos[i].second->getName().compare("R") == 0){
        ((Rook *)availablePos[i].second)->hasMoved = true;
    }
    gameBoard->table[availablePos[i].second->position.first][availablePos[i].second->position.second - 'a' + 1] = NULL;
    if (enPassant != 1) {
        captured = gameBoard->table[availablePos[i].first.first][availablePos[i].first.second - 'a' + 1];
    } else {
        captured = gameBoard->table[availablePos[i].second->position.first][availablePos[i].first.second - 'a' + 1];
        gameBoard->table[availablePos[i].second->position.first][availablePos[i].first.second - 'a' + 1] = NULL;
    }

    if(captured != NULL)
        remove(pieces[1 - color], captured);

    if(castle == 1) {
        Piece *piece = availablePos[i].second;
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][8];
        gameBoard->table[piece->position.first][piece->position.second - 'a' + 2] = rook;
        gameBoard->table[piece->position.first][8] = NULL;
        //Actualiza rook's position
        rook->position.second = piece->position.second + 1;
    }
    if(castle == 2) {
        Piece *piece = availablePos[i].second;
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][1];
        gameBoard->table[piece->position.first][piece->position.second -'a'] = rook;
        gameBoard->table[piece->position.first][1] = NULL;
        //Actualiza rook's position
        rook->position.second = piece->position.second - 1;
    }

    // Actualize moved piece position
    availablePos[i].second->position.first = availablePos[i].first.first;
    availablePos[i].second->position.second = availablePos[i].first.second;

    // Promote
    temp = availablePos[i].second;
    if(availablePos[i].first.first == 7 * color + 1) {
        if(temp->getName().compare("P") == 0)
            ok = ((Pawn*)temp)->promote(gameBoard, pieces[color], chosenPromotion);
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
    vector<Piece*> pieces[2];
    Piece *pieceEP = NULL;
    GameBoard* gameBoard = new GameBoard();
    char command[20], protover[20], N;
    // mode: 1 -> bot plays, 0 -> force
    int mode = 1;
    // color: 1 -> black, 0 -> white
    int color = 0;

    srand(time(NULL));
    
    while (true) {
        //sleep(1);
        cin >> command;
	// cout << "Comanda : " << command << endl;
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
            while(strncmp(protover, "force", 5) != 0)
		cin >> protover;
	    mode = 0;
        }
        else if(strncmp(command, "new", 3)==0) {
            gameBoard->init(pieces[0], pieces[1]);
            mode = 1;
            color = 0;
            gameBoard->showBoard();
        }
        else if(strncmp(command, "force", 5) == 0){
            mode = 0;
        }
        else if(strncmp(command, "go", 2) == 0) {
            if (computeNextMove(gameBoard, pieces, color) == -1) {
                cout << "resign" << endl;
            }
            color = 1 - color;
            if (pieceEP != NULL) {
                ((Pawn *)pieceEP)->moved_two = false;
                pieceEP = NULL;
            }
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
                updateOpponentPieces(gameBoard, command, pieces, color, pieceEP);
                if (computeNextMove(gameBoard, pieces, color) == -1) {
                    cout << "resign" << endl;
                }
                if (pieceEP != NULL) {
                    ((Pawn *)pieceEP)->moved_two = false;
                    pieceEP = NULL;
                }
                color = 1 - color;
                gameBoard->showBoard();
            }
            else {
                if (pieceEP != NULL) {
                    ((Pawn *)pieceEP)->moved_two = false;
                    pieceEP = NULL;
                }
                updateOpponentPieces(gameBoard, command, pieces, 1 - color, pieceEP);
                color = 1 - color;
                gameBoard->showBoard();
            }
        }
    }
    return 0;
}
