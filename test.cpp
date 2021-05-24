/* TODO 
    -> verificat pat, sah, 3-check
    -> fct de eval mai buna
    -> promote in computeMove
    -> bate pegasus
*/

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
#define oo 2e9

using namespace std;

vector<Piece*> pieces[2];
GameBoard* gameBoard;
vector<King *> kings;
int fcheck[2] = {200, 1000}; 
int scheck[2] = {1000, 5000}; 
int fchk, schk;

int pawn_matrix[2][9][9] = 
{
    {
    {0,  0,  0,  0,  0,  0,  0,  0},
    {5, 10, 10,-20,-20, 10, 10,  5},
    {5, -5,-10,  0,  0,-10, -5,  5},
    {0,  0,  0, 20, 20,  0,  0,  0},
    {5,  5, 10, 25, 25, 10,  5,  5},
    {10, 10, 20, 30, 30, 20, 10, 10},
    {50, 50, 50, 50, 50, 50, 50, 50},
    {0,  0,  0,  0,  0,  0,  0,  0}
    },
    
    {
    {0,  0,  0,  0,  0,  0,  0,  0},
    {50, 50, 50, 50, 50, 50, 50, 50},
    {10, 10, 20, 30, 30, 20, 10, 10},
    {5,  5, 10, 25, 25, 10,  5,  5},
    {0,  0,  0, 20, 20,  0,  0,  0},
    {5, -5,-10,  0,  0,-10, -5,  5},
    {5, 10, 10,-20,-20, 10, 10,  5},
    {0,  0,  0,  0,  0,  0,  0,  0}
    }
};
int knight_matrix[2][9][9] =
{
    {
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  0,  5,  5,  0,-20,-40},
    {-30,  5, 10, 15, 15, 10,  5,-30},
    {-30,  0, 15, 20, 20, 15,  0,-30},
    {-30,  5, 15, 20, 20, 15,  5,-30},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-40,-20,  0,  0,  0,  0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50} 
    },
    {
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  0,  0,  0,  0,-20,-40},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-30,  5, 15, 20, 20, 15,  5,-30},
    {-30,  0, 15, 20, 20, 15,  0,-30},
    {-30,  5, 10, 15, 15, 10,  5,-30},
    {-40,-20,  0,  5,  5,  0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50}
    }
};
int bishop_matrix[2][9][9] =
{
    {
    {-20,-10,-10,-10,-10,-10,-10,-20},
    {-10,  5,  0,  0,  0,  0,  5,-10},
    {-10, 10, 10, 10, 10, 10, 10,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},   
    {-10,  5,  5, 10, 10,  5,  5,-10},
    {-10,  0,  5, 10, 10,  5,  0,-10},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-20,-10,-10,-10,-10,-10,-10,-20}
    },
    {
    {-20,-10,-10,-10,-10,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5, 10, 10,  5,  0,-10},
    {-10,  5,  5, 10, 10,  5,  5,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10, 10, 10, 10, 10, 10, 10,-10},
    {-10,  5,  0,  0,  0,  0,  5,-10},
    {-20,-10,-10,-10,-10,-10,-10,-20}
    }
};
int rook_matrix[2][9][9] =
{
    {
    {0,  0,  0,  5,  5,  0,  0,  0},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {5, 10, 10, 10, 10, 10, 10,  5},
    {0,  0,  0,  0,  0,  0,  0,  0},
    },
    {
    {0,  0,  0,  0,  0,  0,  0,  0},
    {5, 10, 10, 10, 10, 10, 10,  5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {0,  0,  0,  5,  5,  0,  0,  0}
    }
};
int queen_matrix[2][9][9] =
{
    {
    {-20,-10,-10, -5, -5,-10,-10,-20},
    {-10,  0,  5,  0,  0,  0,  0,-10},
    {-10,  5,  5,  5,  5,  5,  0,-10},
    {0,  0,  5,  5,  5,  5,  0, -5},
    {-5,  0,  5,  5,  5,  5,  0, -5},
    {-10,  0,  5,  5,  5,  5,  0,-10},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-20,-10,-10, -5, -5,-10,-10,-20}
    },
    {
    {-20,-10,-10, -5, -5,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5,  5,  5,  5,  0,-10},
    {-5,  0,  5,  5,  5,  5,  0, -5},
    {0,  0,  5,  5,  5,  5,  0, -5},
    {-10,  5,  5,  5,  5,  5,  0,-10},
    {-10,  0,  5,  0,  0,  0,  0,-10},
    {-20,-10,-10, -5, -5,-10,-10,-20}
    }
};
int king_matrix[2][9][9] =
{
    {
    {20, 30, 10,  0,  0, 10, 30, 20},
    {20, 20,  0,  0,  0,  0, 20, 20},
    {-10,-20,-20,-20,-20,-20,-20,-10},
    {-20,-30,-30,-40,-40,-30,-30,-20},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    },
    {
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-20,-30,-30,-40,-40,-30,-30,-20},
    {-10,-20,-20,-20,-20,-20,-20,-10},
    {20, 20,  0,  0,  0,  0, 20, 20},
    {20, 30, 10,  0,  0, 10, 30, 20}
    }
};
void remove(vector<Piece*> &pieces, Piece* piece){
    int i, sz = pieces.size();
    for(i = 0; i < sz; i++)
        if(pieces[i] == piece)
            break;
    //Remove piece if found
    if(i != sz)
        pieces.erase(pieces.begin() + i);
}

void removeMove(Piece *&piece, pair<int, char> move, pair<int, char> old_p, int color, Piece *&captured, int moved, int promoted, int kingCheck){
    if (kingCheck == 0)
        kings[color]->stillAlive--;
    piece->position.first = old_p.first;
    piece->position.second = old_p.second;
    int castle = 0;
    if(piece->name == 'K'){
        if(moved == 1)
            ((King *)piece)->hasMoved = false;
    }
    if(piece->name == 'R'){
        if(moved == 1)
            ((Rook *)piece)->hasMoved = false;
    }
    //Castle king side
    if(piece->name == 'K' && move.second - piece->position.second == 2){
        castle = 1;
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][piece->position.second - 'a' + 2];
        gameBoard->table[piece->position.first][piece->position.second - 'a' + 2] = NULL;
        gameBoard->table[piece->position.first][8] = rook;
        rook->position.first = piece->position.first;
        rook->position.second = 'h';
    }
    //Castle queen side
    if(piece->name == 'K' && move.second - piece->position.second == -2){
        castle = 2;
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][piece->position.second - 'a'];
        gameBoard->table[piece->position.first][piece->position.second - 'a'] = NULL;
        gameBoard->table[piece->position.first][1] = rook;
        rook->position.first = piece->position.first;
        rook->position.second = 'a';
    }
    if(captured != NULL)
        gameBoard->table[captured->position.first][captured->position.second - 'a' + 1] = captured;
    else
        gameBoard->table[move.first][move.second - 'a' + 1] = captured;
    // En passant
    if(captured && (captured->position.first != move.first || captured->position.second != move.second)){
        gameBoard->table[move.first][move.second - 'a' + 1] = NULL;
    }


    // Promote
    if(promoted == 1) {
        if (piece->name == 'Q') {
            gameBoard->table[move.first][move.second - 'a' + 1] = NULL;
            remove(pieces[color], piece);
            Pawn *pawn = new Pawn(make_pair(old_p.first, old_p.second), color);
            gameBoard->table[old_p.first][old_p.second - 'a' + 1] = pawn;     
        }
    }
    else {
        gameBoard->table[piece->position.first][piece->position.second - 'a' + 1] = piece;
    }


    /*if(captured && captured->color != color){
        cout << castle << " nu e ok " << captured->getName() << captured->color << ' ' << captured->position.first << ' ' << captured->position.second << endl;
        cout << piece->getName() << piece->color << ' ' << move.first << ' ' << move.second << endl;
        gameBoard->showBoard();
    }*/
    if(captured != NULL)
        pieces[color].push_back(captured);
}
int verify_ok(int x, int y, int color){
    for (int i = x - 1; i >= 1; i--) {
        if (gameBoard->table[i][y - 'a' + 1] == NULL) {
            continue;
        }
        else if(gameBoard->table[i][y - 'a' + 1]->color != color)
        {
            Piece *piece = gameBoard->table[i][y - 'a' + 1];
            if(piece->name == 'Q' || piece->name == 'R')
                return 0;
            if(piece->name == 'K' && x - i == 1)
                return 0;
            break;
        }
        else {
            break;
        }
    }
    // check lower line
    for (int i = x + 1; i <= 8; i++) {
        if (gameBoard->table[i][y - 'a' + 1] == NULL) {
            continue;
        }
        else if(gameBoard->table[i][y - 'a' + 1]->color != color)
        {
            Piece *piece = gameBoard->table[i][y - 'a' + 1];
            if(piece->name == 'Q' || piece->name == 'R')
                return 0;
            if(piece->name == 'K' && i - x == 1)
                return 0;
            break;
        }
        else {
            break;
        }
    }
    // check right line
    for (int i = y + 1; i <= 'h'; i++) {
        if (gameBoard->table[x][i - 'a' + 1] == NULL) {
            continue;
        }
        else if(gameBoard->table[x][i - 'a' + 1]->color != color)
        {
            Piece *piece = gameBoard->table[x][i - 'a' + 1];
            if(piece->name == 'Q' || piece->name == 'R')
                return 0;
            if(piece->name == 'K' && i - y == 1)
                return 0;
            break;
        }
        else {
            break;
        }
    }
    // check left line
    for (int i = y - 1; i >= 'a'; i--) {
        if (gameBoard->table[x][i - 'a' + 1] == NULL) {
            continue;
        }
        else if(gameBoard->table[x][i - 'a' + 1]->color != color)
        {
            Piece *piece = gameBoard->table[x][i - 'a' + 1];
            if(piece->name == 'Q' || piece->name == 'R')
                return 0;
            if(piece->name == 'K' && y - i == 1)
                return 0;
            break;
        }
        else {
            break;
        }
    }
    // check superior main diagonal
    int i; char j;
    for (i = x - 1, j = y - 1; i >= 1 && j >= 'a'; i--, j--) {
        if (gameBoard->table[i][j - 'a' + 1] == NULL) {
            continue;
        }
        else if(gameBoard->table[i][j - 'a' + 1]->color != color)
        {
            Piece *piece = gameBoard->table[i][j - 'a' + 1];
            if(piece->name == 'Q' || piece->name == 'B')
                return 0;
            if(piece->name == 'K' && y - j == 1 && x - i == 1)
                return 0;
            if(piece->name == 'P' && piece->color == 0 && y - j == 1 && x - i == 1)
                return 0;
            break;
        }
        else {
            break;
        }
    }
    // check inferior main diagonal
    for (i = x + 1, j = y + 1; i <= 8 && j <= 'h'; i++, j++) {
        if (gameBoard->table[i][j - 'a' + 1] == NULL) {
            continue;
        }
        else if(gameBoard->table[i][j - 'a' + 1]->color != color)
        {
            Piece *piece = gameBoard->table[i][j - 'a' + 1];
            if(piece->name == 'Q' || piece->name == 'B')
                return 0;
            if(piece->name == 'K' && j - y == 1 && i - x == 1)
                return 0;
            if(piece->name == 'P' && piece->color == 1 && j - y == 1 && i - x == 1)
                return 0;
            break;
        }
        else {
            break;
        }
    }
    // check inferior second diagonal
    for (i = x + 1, j = y - 1; i <=8 && j >= 'a'; i++, j--) {
        if (gameBoard->table[i][j - 'a' + 1] == NULL) {
            continue;
        }
        else if(gameBoard->table[i][j - 'a' + 1]->color != color)
        {
            Piece *piece = gameBoard->table[i][j - 'a' + 1];
            if(piece->name == 'Q' || piece->name == 'B')
                return 0;
            if(piece->name == 'K' && y - j == 1 && i - x == 1)
                return 0;
            if(piece->name == 'P' && piece->color == 0 && y - j == 1 && i - x == 1)
                return 0;
            break;
        }
        else {
            break;
        }
    }
    // check superior second diagonal
    for (i = x - 1, j = y + 1; i >= 1 && j <= 'h'; i--, j++) {
        if (gameBoard->table[i][j - 'a' + 1] == NULL) {
            continue;
        }
        else if(gameBoard->table[i][j - 'a' + 1]->color != color)
        {
            Piece *piece = gameBoard->table[i][j - 'a' + 1];
            if(piece->name == 'Q' || piece->name == 'B')
                return 0;
            if(piece->name == 'K' && j - y == 1 && x - i == 1)
                return 0;
            if(piece->name == 'P' && piece->color == 1 && j - y == 1 && x - i == 1)
                return 0;
            break;
        }
        else {
            break;
        }
    }
    int vx[] = {1, 2, 2, 1, -1, -2, -2, -1};
    int vy[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int X, Y;

    for(i = 0; i < 8; i++){
        X = x + vx[i];
        Y = y + vy[i];
        if(X < 9 && X > 0 && Y >= 'a' && Y <= 'h'){
            if (gameBoard->table[X][Y - 'a' + 1] == NULL)
                continue;
            else if(gameBoard->table[X][Y - 'a' + 1]->color != color)
            {
                Piece *piece = gameBoard->table[X][Y - 'a' + 1];
                if(piece->name == 'N')
                    return 0;
                break;
            }
        }
    }
    return 1;
}
int in_check(int castle, int color){
    int x = kings[color]->position.first;
    int y = kings[color]->position.second;
    if(castle == 0)
        return verify_ok(x, y, color);
    if(castle == 1){
        int ok = verify_ok(x, y, color);
        if(!ok)
            return 0;
        ok = verify_ok(x, y - 1, color);
        if(!ok)
            return 0;
        return verify_ok(x, y - 2, color);
    }
    if(castle == 2){
        int ok = verify_ok(x, y, color);
        if(!ok)
            return 0;
        ok = verify_ok(x, y + 1, color);
        if(!ok)
            return 0;
        return verify_ok(x, y + 2, color);
    }
    return 0;
}
int tryMove(Piece *piece, pair<int, char> move, pair<int, char> &old_p, int color, Piece *&captured){
    //Castle king side
    
    int castle = 0;
    if(piece->name == 'K' && move.second - piece->position.second == 2){
        castle = 1;
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][8];
        gameBoard->table[piece->position.first][piece->position.second - 'a' + 2] = rook;
        gameBoard->table[piece->position.first][8] = NULL;
    }
    //Castle queen side
    if(piece->name == 'K' && move.second - piece->position.second == -2){
        castle = 2;
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][1];
        gameBoard->table[piece->position.first][piece->position.second -'a'] = rook;
        gameBoard->table[piece->position.first][1] = NULL;
    }
    if(piece->name == 'P' && abs(move.second - piece->position.second) == 1 
    && abs(move.first - piece->position.first) == 1 && gameBoard->table[move.first][move.second - 'a' + 1] == NULL){
        captured = gameBoard->table[piece->position.first][move.second - 'a' + 1];
        gameBoard->table[piece->position.first][move.second - 'a' + 1] = NULL;
    }
    else
        captured = gameBoard->table[move.first][move.second - 'a' + 1];


    // Promote
    char chosenPromotion = 'q';
    if(piece->name == 'P' && move.first == 7 * color + 1) {
        ((Pawn*)piece)->promote(gameBoard, pieces[color], chosenPromotion);
    }

    gameBoard->table[piece->position.first][piece->position.second - 'a' + 1] = NULL;
    gameBoard->table[move.first][move.second - 'a' + 1] = piece;
    if(captured != NULL)
        remove(pieces[color], captured);

    vector<pair<pair<int, char>, Piece*>> moves;
    vector<pair<pair<int, char>, Piece*>> aux;
    int sz = pieces[1 - color].size(), i;
    
    old_p.first = piece->position.first;
    old_p.second = piece->position.second;
    piece->position.first = move.first;
    piece->position.second = move.second;
    int ok = in_check(castle, 1 - color);
    return ok;
}

void apply_move(Piece *&piece, pair<int, char> move, pair<int, char> &old_p, int color, Piece *&captured, int &moved, int &promote, int &checkKing){
    moved = 0;
    promote = 0;
    checkKing = 1;
    if(piece->name == 'K'){
        if(((King *)piece)->hasMoved == true)
            moved = 2;
        else
            moved = 1;
        ((King *)piece)->hasMoved = true;
    }
    if(piece->name == 'R'){
        if(((Rook *)piece)->hasMoved == true)
            moved = 2;
        else
            moved = 1;
        ((Rook *)piece)->hasMoved = true;
    }
    //Castle king side
    if(piece->name == 'K' && move.second - piece->position.second == 2){
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][8];
        gameBoard->table[piece->position.first][piece->position.second - 'a' + 2] = rook;
        gameBoard->table[piece->position.first][8] = NULL;
        rook->position.first = piece->position.first;
        rook->position.second = piece->position.second + 1;
    }
    //Castle queen side
    if(piece->name == 'K' && move.second - piece->position.second == -2){
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][1];
        gameBoard->table[piece->position.first][piece->position.second -'a'] = rook;
        gameBoard->table[piece->position.first][1] = NULL;
        rook->position.first = piece->position.first;
        rook->position.second = piece->position.second - 1;
    }
    if(piece->name == 'P' && abs(move.second - piece->position.second) == 1 
    && abs(move.first - piece->position.first) == 1 && gameBoard->table[move.first][move.second - 'a' + 1] == NULL){
        captured = gameBoard->table[piece->position.first][move.second - 'a' + 1];
        gameBoard->table[piece->position.first][move.second - 'a' + 1] = NULL;
    }
    else
        captured = gameBoard->table[move.first][move.second - 'a' + 1];
    
    // Promote
    char chosenPromotion = 'q';
    if(piece->name == 'P' && move.first == 7 * color + 1) {
        ((Pawn*)piece)->promote(gameBoard, pieces[color], chosenPromotion);
        promote = 1;
    }
    
    gameBoard->table[piece->position.first][piece->position.second - 'a' + 1] = NULL;
    gameBoard->table[move.first][move.second - 'a' + 1] = piece;
    if(captured != NULL)
        remove(pieces[color], captured);

    old_p.first = piece->position.first;
    old_p.second = piece->position.second;
    piece->position.first = move.first;
    piece->position.second = move.second;
    checkKing = in_check(0, color);
    if (checkKing == 0)
        kings[color]->stillAlive++;
}

vector<pair<pair<int, char>, Piece*>> computePositions(int color){
    vector<pair<pair<int, char>, Piece*>> moves;
    vector<pair<pair<int, char>, Piece*>> goodMoves;
    Piece *captured;
    int sz = pieces[color].size(), sz2, i, j;
    pair <int, char> old_p;
    for(i = 0; i < sz; i++) {
        moves = pieces[color][i]->findPositions(gameBoard);
        sz2 = moves.size();
        for(j = 0; j < sz2; j++) {
            if(tryMove(pieces[color][i], moves[j].first, old_p, 1 - color, captured))
                goodMoves.push_back(moves[j]);
            removeMove(pieces[color][i], moves[j].first, old_p, 1 - color, captured, 0, 0, 1);
        }
    }
    return goodMoves;
}

void updateOpponentPieces(string command, int color, Piece *&pieceEP) {
    // Update table
    Piece *aux =  gameBoard->table[9 - (command[1] - '0')][command[0] - 'a' + 1];
    Piece *piece = aux;
    Piece *captured = NULL;
    if(piece->name == 'K')
        ((King *)piece)->hasMoved = true;

    if(piece->name == 'R')
        ((Rook *)piece)->hasMoved = true;
    // CASTLE
    if(piece->name == 'K' && command[2] - piece->position.second == 2){
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][8];
        gameBoard->table[piece->position.first][piece->position.second - 'a' + 2] = rook;
        gameBoard->table[piece->position.first][8] = NULL;
        rook->position.second = piece->position.second + 1;
    }
    //Castle queen side
    if(piece->name == 'K' && command[2] - piece->position.second == -2){
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][1];
        gameBoard->table[piece->position.first][piece->position.second -'a'] = rook;
        gameBoard->table[piece->position.first][1] = NULL;
        rook->position.second = piece->position.second - 1;
    }
    // En passant
    if(piece->name == 'P' && abs(command[3] - command[1]) == 2) {
        pieceEP = piece;
        ((Pawn *)piece)->moved_two = true;
    }
    // En passant capture
    if (piece->name == 'P' && abs(command[3] - command[1]) == 1
    && abs(command[2] - command[0]) == 1 && gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1] == NULL) {
        captured = gameBoard->table[9 - (command[1] - '0')][command[2] - 'a' + 1];
        gameBoard->table[9 - (command[1] - '0')][command[2] - 'a' + 1] = NULL;
    } else {
        captured = gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1];
    }
    gameBoard->table[9 - (command[1] - '0')][command[0] - 'a' + 1] = NULL;
    gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1] = aux;
    aux->position.first = 9 - (command[3] - '0');
    aux->position.second = command[2];

    // Remove if captured
    if(captured != NULL) {
        remove(pieces[captured->color], captured);
    }
    Piece *temp = gameBoard->table[9 - (command[3] - '0')][command[2] - 'a' + 1];

    // Promote
    if (temp->position.first == 7 * (1 - color) + 1) {
        if (temp->name == 'P') {
            ((Pawn *)temp)->promote(gameBoard, pieces[1 - color], command[4]); 
        }
    }

    // Check if in check
    int ok = in_check(0, color);
    if(!ok)
        kings[color]->stillAlive++;
    cout << "vieti rege " <<  kings[color]->stillAlive << endl;
    if(kings[color]->stillAlive == 3)
        cout << "am pierdut" << endl;

}

// compute the state score for current player
int evaluate(int player) {
    int score = 0;
    int x;
    char y;
    if(in_check(0, player) == 0){
        if(kings[player]->stillAlive == 1)
            score -= 200;
        else if(kings[player]->stillAlive == 2)
            score -= 1000;
        else
            return -oo + 10; 
    }
    for(auto piece : pieces[player]){
        y = piece->position.second - 'a';
        if(player == 0)
            x = piece->position.first - 1;
        else
            x = 9 - piece->position.first - 1;
        if(piece->name == 'P')
            score += 100 + pawn_matrix[1 - player][x][y];
        else if(piece->name == 'N')
            score += 320 + knight_matrix[1 - player][x][y];
        else if(piece->name == 'B')
            score += 330 + bishop_matrix[1- player][x][y];
        else if(piece->name == 'R')
            score += 500 + rook_matrix[1 - player][x][y];
        else if(piece->name == 'Q')
            score += 900 + queen_matrix[1- player][x][y];
        else if(piece->name == 'K')
            score += 20000 + king_matrix[1 - player][x][y];
    }
    if(in_check(0, 1 - player) == 0){
        if(kings[1 - player]->stillAlive == 1)
            score += 200;
        else if(kings[1 - player]->stillAlive == 2)
            score += 1000;
        else
            return oo - 10; 
    }
    for(auto piece : pieces[1 - player]){
        y = piece->position.second - 'a';
         if(player == 0)
            x = piece->position.first - 1;
        else
            x = 9 - piece->position.first - 1;
        if(piece->name == 'P')
            score -= 100 + pawn_matrix[player][x][y];
        else if(piece->name == 'N')
            score -= 320 + knight_matrix[player][x][y];
        else if(piece->name == 'B')
            score -= 330 + bishop_matrix[player][x][y];
        else if(piece->name == 'R')
            score -= 500 + rook_matrix[player][x][y];
        else if(piece->name == 'Q')
            score -= 900 + queen_matrix[player][x][y];
        else if(piece->name == 'K')
            score -= 20000 + king_matrix[player][x][y];
    }
    return score;
}
 
// apply the move on the current state: old_state -> new_state
//void apply_move(state, move);
// undo the move and restore previous state: new_state -> old_state
//void undo_move(state, move);
 
// check if any player won the game
//bool game_over(state);
  
// compute the best score that player can get,
// considering that the opponent also has an optimal strategy


//TODO -> promote in apply_move + remove_move !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int alphabeta_negamax(int depth, int player, pair<pair<int, char>, Piece*> &best_move, int alpha, int beta) {
    //void applyMove(Piece *piece, pair<int, char> move, pair<int, char> &old_p, GameBoard *gameBoard, vector<Piece*> pieces[], int color, Piece *&captured){
    // STEP 1: game over or maximum recursion depth was reached
    if (kings[player]->stillAlive == 3) {
        return -oo + (6 - depth);
    }
    if (depth == 0) {
       return evaluate(player);
    }
 
    // STEP 2: generate all possible moves for player
    //gameBoard->showBoard();
    //cout << "Before compute moves " << endl;
    vector<pair<pair<int, char>, Piece*>> all_moves = computePositions(player);
    //cout << "After compute moves " << endl;
    //gameBoard->showBoard();
    if (all_moves.empty()) {
        int ok = in_check(0, player);
        if (ok)
            return 0;
        else
            return -oo + 1;
    }
    /*cout << depth << endl;
    for(auto piece : pieces[player])
        cout << piece->getName() << ' ';
    cout << endl;
    for (auto move : all_moves) 
        cout << move.first.first << ' ' << move.first.second << ' ' << move.second->getName() << endl; 
    cout << endl;*/
    // STEP 3: try to apply each move - compute best score
    int best_score = -oo;
    Piece *captured;
    pair <int, char> old_p;
    pair<pair<int, char>, Piece*> best_move_aux;
    for (auto move : all_moves) {
        // STEP 3.1: do move
        captured = NULL;
        //cout << depth << ' ' << player << ' ' << move.first.first << ' ' << move.first.second << ' ' << move.second->getName() << endl;
        //gameBoard->showBoard();
        int moved, promoted, kingCheck = 0;
        
        apply_move(move.second, move.first, old_p, 1 - player, captured, moved, promoted, kingCheck);
        
        //cout<<endl;
        //gameBoard->showBoard();
        //cout << endl;
        /*if(player != move.second->color)
            cout << "WTF! " << move.second->getName() << "  " << move.first.first << ' ' << move.first.second << endl;*/
        // STEP 3.2: play for the opponent
        int score = -alphabeta_negamax(depth - 1, 1 - player, best_move_aux, -beta, -alpha);
        //if(depth == 3)
        //if(move.second->name == 'K' && depth == 5)
        //    cout << score << ' ' << move.first.first << ' ' << move.first.second << endl;
             
        // opponent allows player to obtain this score if player will do current move.
        // player chooses this move only if it has a better score.
        if (score > best_score) {
            best_score = score;

            // [optional]: the best move can be saved
           
            best_move = move;
            /*if(depth == 3)
                cout << "deadawdwd" << ' ' << best_move.first.first << ' ' << best_move.first.second << ' ' << best_move.second->getName() << endl; 
        */}
        if (best_score > alpha) {
            alpha = best_score;
        }
        //cout << "cv1" << endl;
        if (alpha >= beta) {
            removeMove(move.second, move.first, old_p, 1 - player, captured, moved, promoted, kingCheck);
            break;
        }
        //cout << "cv2" << endl;
        // void removeMove(Piece *piece, pair<int, char> move, pair<int, char> old_p, GameBoard *gameBoard, vector<Piece*> pieces[], int color, Piece *&captured){
        // STEP 3.3: undo move
        removeMove(move.second, move.first, old_p, 1 - player, captured, moved, promoted, kingCheck);
        //cout << "cv3" << endl;
        //gameBoard->showBoard();
    }
 
    // STEP 4: return best allowed score
    // [optional] also return the best move
    return best_score;
}

int computeNextMove(int color, int depth) {
    int i, ok = 0;
    vector<pair<pair<int, char>, Piece*>> pos;
    Piece *captured, *temp;
    vector<char> possiblePromotes = {'q', 'r', 'b', 'n'};
    char chosenPromotion = 'q';
    
    pair<pair<int, char>, Piece*> move;
    cout << "before choosing" << endl;
    alphabeta_negamax(5, color, move, -oo, oo);
    cout << "chose a move" << endl;
    cout << move.first.first << ' ' << move.first.second << ' ' << move.second->name << endl;
    cout << "cv" << endl;
    int castle = 0, enPassant = 0;
    // castle
    if(move.second->name == 'K'){
        if(move.second->position.second - move.first.second == 2){
            castle = 2;
            enPassant = 0;
        }
        if(move.second->position.second - move.first.second == -2){
            castle = 1;
            enPassant = 0;
        }
    }
    if (move.second->name == 'P') {
        if (move.second->position.second != move.first.second 
        && gameBoard->table[move.first.first][move.first.second - 'a' + 1] == NULL) {
            enPassant = 1;
        }
    }
    // Print the move
    if (move.first.first == 7 * color + 1 && move.second->name == 'P') {
        chosenPromotion = possiblePromotes[rand() % 4];
        cout << "move " << move.second->position.second << 9 - move.second->position.first 
        << move.first.second << 9 - move.first.first << chosenPromotion << endl;
    } else {
        cout << "move " << move.second->position.second << 9 - move.second->position.first 
        << move.first.second << 9 - move.first.first << endl;
    }

    // Actualize position on table
    if(move.second->name == 'K'){
        ((King *)move.second)->hasMoved = true;
    }
    if(move.second->name == 'R'){
        ((Rook *)move.second)->hasMoved = true;
    }
    gameBoard->table[move.second->position.first][move.second->position.second - 'a' + 1] = NULL;
    if (enPassant != 1) {
        captured = gameBoard->table[move.first.first][move.first.second - 'a' + 1];
    } else {
        captured = gameBoard->table[move.second->position.first][move.first.second - 'a' + 1];
        gameBoard->table[move.second->position.first][move.first.second - 'a' + 1] = NULL;
    }

    if(captured != NULL)
        remove(pieces[1 - color], captured);

    if(castle == 1){
        Piece *piece = move.second;
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][8];
        gameBoard->table[piece->position.first][piece->position.second - 'a' + 2] = rook;
        gameBoard->table[piece->position.first][8] = NULL;
        //Actualiza rook's position
        rook->position.second = piece->position.second + 1;
    }
    if(castle == 2){
        Piece *piece = move.second;
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][1];
        gameBoard->table[piece->position.first][piece->position.second -'a'] = rook;
        gameBoard->table[piece->position.first][1] = NULL;
        //Actualiza rook's position
        rook->position.second = piece->position.second - 1;
    }

    // Actualize moved piece position
    move.second->position.first = move.first.first;
    move.second->position.second = move.first.second;

    // Promote
    temp = move.second;
    if(move.first.first == 7 * color + 1) {
        if(temp->name == 'P')
            ok = ((Pawn*)temp)->promote(gameBoard, pieces[color], chosenPromotion);
    }

    if (ok == 0)
        gameBoard->table[move.first.first][move.first.second - 'a' + 1] = move.second;
    if(!in_check(0, 1 - color))
        kings[1 - color]->stillAlive++;
    return 1;
}

int main() {
    int T;
    vector<pair<pair<int, char>, Piece*>> availablePos;
    vector<pair<pair<int, char>, Piece*>> pos;
    int depth = 6;
    // pieces[0] -> white's pieces; pieces[1] -> black's pieces
    Piece *pieceEP = NULL;
    gameBoard = new GameBoard();
    char command[20], protover[20], N;
    // mode: 1 -> bot plays, 0 -> force
    int mode = 1;
    // color: 1 -> black, 0 -> white
    int color = 0;

    srand(time(NULL));
    //fchk = fcheck[1];
    //schk = fcheck[1];
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
        else if (strncmp(command, "variant", 7) == 0) {
            cin >> command;
        }
        else if (strncmp(command, "result", 6) == 0) {
	    cin >> protover;
            while(strncmp(protover, "force", 5) != 0)
		cin >> protover;
	    mode = 0;
        }
        else if(strncmp(command, "new", 3)==0) {
            gameBoard->init(pieces[0], pieces[1]);
            kings.push_back((King *)gameBoard->table[8][5]);
            kings.push_back((King *)gameBoard->table[1][5]);
            mode = 1;
            color = 0;
            gameBoard->showBoard();
        }
        else if(strncmp(command, "force", 5) == 0){
            mode = 0;
        }
        else if(strncmp(command, "go", 2) == 0) {
            
            if (computeNextMove(color, depth) == -1) {
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
            cin >> T;
            if(strncmp(command, "time", 4) == 0) 
                if(T < 9000)
                    depth = 5;
                else if(T > 12000)
                    depth = 6;
        }
        else {
            if(mode == 1) {
                color = 1 - color;
                fchk = fcheck[color];
                schk = scheck[color];
                updateOpponentPieces(command, color, pieceEP);
                gameBoard->showBoard();
                if (computeNextMove(color, depth) == -1) {
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
                updateOpponentPieces(command, 1 - color, pieceEP);
                color = 1 - color;
                gameBoard->showBoard();
            }
        }
    }
    return 0;
}