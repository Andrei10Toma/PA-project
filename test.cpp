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

int pawn_matrix[9][9] = 
{
    {0,  0,  0,  0,  0,  0,  0,  0},
    {50, 50, 50, 50, 50, 50, 50, 50},
    {10, 10, 20, 30, 30, 20, 10, 10},
    {5,  5, 10, 25, 25, 10,  5,  5},
    {0,  0,  0, 20, 20,  0,  0,  0},
    {5, -5,-10,  0,  0,-10, -5,  5},
    {5, 10, 10,-20,-20, 10, 10,  5},
    {0,  0,  0,  0,  0,  0,  0,  0}
};
int knight_matrix[9][9] =
{
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  0,  0,  0,  0,-20,-40},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-30,  5, 15, 20, 20, 15,  5,-30},
    {-30,  0, 15, 20, 20, 15,  0,-30},
    {-30,  5, 10, 15, 15, 10,  5,-30},
    {-40,-20,  0,  5,  5,  0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50}
};
int bishop_matrix[9][9] =
{
    {-20,-10,-10,-10,-10,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5, 10, 10,  5,  0,-10},
    {-10,  5,  5, 10, 10,  5,  5,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10, 10, 10, 10, 10, 10, 10,-10},
    {-10,  5,  0,  0,  0,  0,  5,-10},
    {-20,-10,-10,-10,-10,-10,-10,-20}
};
int rook_matrix[9][9] =
{
    {0,  0,  0,  0,  0,  0,  0,  0},
    {5, 10, 10, 10, 10, 10, 10,  5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {0,  0,  0,  5,  5,  0,  0,  0}
};
int queen_matrix[9][9] =
{
    {-20,-10,-10, -5, -5,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5,  5,  5,  5,  0,-10},
    {-5,  0,  5,  5,  5,  5,  0, -5},
    {0,  0,  5,  5,  5,  5,  0, -5},
    {-10,  5,  5,  5,  5,  5,  0,-10},
    {-10,  0,  5,  0,  0,  0,  0,-10},
    {-20,-10,-10, -5, -5,-10,-10,-20}
};
int king_matrix[9][9] =
{
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-20,-30,-30,-40,-40,-30,-30,-20},
    {-10,-20,-20,-20,-20,-20,-20,-10},
    {20, 20,  0,  0,  0,  0, 20, 20},
    {20, 30, 10,  0,  0, 10, 30, 20}
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

void removeMove(Piece *piece, pair<int, char> move, pair<int, char> old_p, GameBoard *gameBoard, vector<Piece*> pieces[], int color, Piece *&captured){
    piece->position.first = old_p.first;
    piece->position.second = old_p.second;
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
    // En passant
    if(captured && (captured->position.first != move.first || captured->position.second != move.second)){
        gameBoard->table[move.first][move.second - 'a' + 1] = NULL;
    }

    gameBoard->table[piece->position.first][piece->position.second - 'a' + 1] = piece;
    if(captured != NULL)
        pieces[color].push_back(captured);
}

int tryMove(Piece *piece, pair<int, char> move, pair<int, char> &old_p, GameBoard *gameBoard, vector<Piece*> pieces[], int color, Piece *&captured){
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
    if(captured != NULL)
        remove(pieces[color], captured);

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
    
    old_p.first = piece->position.first;
    old_p.second = piece->position.second;
    piece->position.first = move.first;
    piece->position.second = move.second;

    return ok;
}

void apply_move(Piece *piece, pair<int, char> move, pair<int, char> &old_p, GameBoard *&gameBoard, vector<Piece*> pieces[], int color, Piece *&captured){
    //Castle king side
    if(piece->getName().compare("K") == 0 && move.second - piece->position.second == 2){
        Rook *rook = (Rook *)gameBoard->table[piece->position.first][8];
        gameBoard->table[piece->position.first][piece->position.second - 'a' + 2] = rook;
        gameBoard->table[piece->position.first][8] = NULL;
    }
    //Castle queen side
    if(piece->getName().compare("K") == 0 && move.second - piece->position.second == -2){
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
    if(captured != NULL)
        remove(pieces[color], captured);

    
    old_p.first = piece->position.first;
    old_p.second = piece->position.second;
    piece->position.first = move.first;
    piece->position.second = move.second;
}

vector<pair<pair<int, char>, Piece*>> computePositions(GameBoard *gameBoard, vector<Piece*> pieces[], int color){
    vector<pair<pair<int, char>, Piece*>> moves;
    vector<pair<pair<int, char>, Piece*>> goodMoves;
    Piece *captured;
    int sz = pieces[color].size(), sz2, i, j;
    pair <int, char> old_p;
    for(i = 0; i < sz; i++) {
        moves = pieces[color][i]->findPositions(gameBoard);
        sz2 = moves.size();
        for(j = 0; j < sz2; j++) {
            if(tryMove(pieces[color][i], moves[j].first, old_p, gameBoard, pieces, 1 - color, captured))
                goodMoves.push_back(moves[j]);
            removeMove(pieces[color][i], moves[j].first, old_p, gameBoard, pieces, 1 - color, captured);
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
        if (temp->getName().compare("P") == 0) {
            ((Pawn *)temp)->promote(gameBoard, pieces[1 - color], command[4]); 
        }
    }
}

// compute the state score for current player
int evaluate(GameBoard *&gameBoard, int player, vector<Piece*> pieces[]) {
    int score = 0;
    for(auto piece : pieces[player]){
        if(piece->getName().compare("P") == 0)
            score += 100 + pawn_matrix[9 - piece->position.first - 1][piece->position.second - 'a'];
        else if(piece->getName().compare("N") == 0)
            score += 320 + knight_matrix[9 - piece->position.first - 1][piece->position.second - 'a'];
        else if(piece->getName().compare("B") == 0)
            score += 330 + bishop_matrix[9 - piece->position.first - 1][piece->position.second - 'a'];
        else if(piece->getName().compare("R") == 0)
            score += 500 + rook_matrix[9 - piece->position.first - 1][piece->position.second - 'a'];
        else if(piece->getName().compare("Q") == 0)
            score += 900 + queen_matrix[9 - piece->position.first - 1][piece->position.second - 'a'];
        else if(piece->getName().compare("K") == 0)
            score += 20000 + king_matrix[9 - piece->position.first - 1][piece->position.second - 'a'];
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
int negamax(GameBoard *&gameBoard, int depth, int player, vector<Piece*> pieces[], pair<pair<int, char>, Piece*> &best_move) {
    //void applyMove(Piece *piece, pair<int, char> move, pair<int, char> &old_p, GameBoard *gameBoard, vector<Piece*> pieces[], int color, Piece *&captured){
    // STEP 1: game over or maximum recursion depth was reached
    if (depth == 0) {
       return evaluate(gameBoard, player, pieces);
    }
 
    // STEP 2: generate all possible moves for player
    vector<pair<pair<int, char>, Piece*>> all_moves = computePositions(gameBoard, pieces, player);
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
        apply_move(move.second, move.first, old_p, gameBoard, pieces, 1 - player, captured);
 
        // STEP 3.2: play for the opponent
        int score = -negamax(gameBoard, depth - 1, 1 - player, pieces, best_move_aux);
        // opponent allows player to obtain this score if player will do current move.
        // player chooses this move only if it has a better score.
        if (score > best_score) {
            best_score = score;

            // [optional]: the best move can be saved
           
            best_move = move;
            /*if(depth == 3)
                cout << "deadawdwd" << ' ' << best_move.first.first << ' ' << best_move.first.second << ' ' << best_move.second->getName() << endl; 
        */}
        // void removeMove(Piece *piece, pair<int, char> move, pair<int, char> old_p, GameBoard *gameBoard, vector<Piece*> pieces[], int color, Piece *&captured){
        // STEP 3.3: undo move
        removeMove(move.second, move.first, old_p, gameBoard, pieces, 1 - player, captured);
    }
 
    // STEP 4: return best allowed score
    // [optional] also return the best move
    return best_score;
}

int computeNextMove(GameBoard *gameBoard, vector<Piece*> pieces[], int color) {
    int i, ok = 0;
    vector<pair<pair<int, char>, Piece*>> pos;
    Piece *captured, *temp;
    vector<char> possiblePromotes = {'q', 'r', 'b', 'n'};
    char chosenPromotion = 'q';
    
    pair<pair<int, char>, Piece*> move;
    negamax(gameBoard, 3, color, pieces, move);
    cout << move.first.first << ' ' << move.first.second << ' ' << move.second->getName() << endl; 
    int castle = 0, enPassant = 0;
    // castle
    if(move.second->getName().compare("K") == 0){
        if(move.second->position.second - move.first.second == 2){
            castle = 2;
            enPassant = 0;
        }
        if(move.second->position.second - move.first.second == -2){
            castle = 1;
            enPassant = 0;
        }
    }
    if (move.second->getName().compare("P") == 0) {
        if (move.second->position.second != move.first.second 
        && gameBoard->table[move.first.first][move.first.second - 'a' + 1] == NULL) {
            enPassant = 1;
        }
    }
    // Print the move
    if (move.first.first == 7 * color + 1 && move.second->getName().compare("P") == 0) {
        chosenPromotion = possiblePromotes[rand() % 4];
        cout << "move " << move.second->position.second << 9 - move.second->position.first 
        << move.first.second << 9 - move.first.first << chosenPromotion << endl;
    } else {
        cout << "move " << move.second->position.second << 9 - move.second->position.first 
        << move.first.second << 9 - move.first.first << endl;
    }

    // Actualize position on table
    if(move.second->getName().compare("K") == 0){
        ((King *)move.second)->hasMoved = true;
    }
    if(move.second->getName().compare("R") == 0){
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
        if(temp->getName().compare("P") == 0)
            ok = ((Pawn*)temp)->promote(gameBoard, pieces[color], chosenPromotion);
    }

    if (ok == 0)
        gameBoard->table[move.first.first][move.first.second - 'a' + 1] = move.second;
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
