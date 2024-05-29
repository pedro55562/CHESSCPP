#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>


#include "board.hpp"
#include "piece.hpp"
#include "constants.hpp"

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool containsChar(const std::string& str, char target) {
    for (char c : str) {
        if (c == target) {
            return true; 
        }
    }
    return false; 
}

namespace chess
{ 
//piece moves offsets 
std::vector<int> knight_offsets = {14,18,31,33,-14,-18,-31,-33};
std::vector<int> bishop_offsets = {15,17,-15,-17};
std::vector<int> rook_offsets = {1,16,-1,-16};
std::vector<int> king_offsets = {1,16,-1,-16, 15, 17, -15, -17};
std::vector<int> queen_offsets = {1,16,-1,-16, 15, 17, -15, -17};

std::vector<int> white_pawn_offsets = {16,17,15};
std::vector<int> black_pawn_offsets = {-16,-17,-15};


std::map<char, int> SymbolToType = {
    {'k', KING},
    {'p', PAWN},
    {'n', KNIGHT},
    {'b', BISHOP},
    {'r', ROOK},
    {'q', QUEEN}
};

std::map<int, char > pieceToChar = {
    {0 , '.'},
    {KING | BLACKn,'k'},
    {KING | WHITEn,'K'},
    {BISHOP | BLACKn,'b'},
    {BISHOP | WHITEn,'B'},
    {QUEEN | BLACKn,'q'},
    {QUEEN| WHITEn,'Q'},
    {PAWN | BLACKn,'p'},
    {PAWN | WHITEn,'P'},
    {ROOK | BLACKn,'r'},
    {ROOK | WHITEn,'R'},
    {KNIGHT | BLACKn,'n'},
    {KNIGHT | WHITEn,'N'}
};

std::map<char, int> ranksTOrows = {
    {'1', 0},
    {'2', 1},
    {'3', 2},
    {'4', 3},
    {'5', 4},
    {'6', 5},
    {'7', 6},
    {'8', 7}
};

std::map<int, char> rowsTOranks = {
    {0, '1'},
    {1, '2'},
    {2, '3'},
    {3, '4'},
    {4, '5'},
    {5, '6'},
    {6, '7'},
    {7, '8'}
};

std::map<char, int> filesTOcols = {
    {'h', 7},
    {'g', 6},
    {'f', 5},
    {'e', 4},
    {'d', 3},
    {'c', 2},
    {'b', 1},
    {'a', 0}
};

std::map<int, char> colsTOfiles = {
    {7, 'h'},
    {6, 'g'},
    {5, 'f'},
    {4, 'e'},
    {3, 'd'},
    {2, 'c'},
    {1, 'b'},
    {0, 'a'}
};

bool Board::isSquareUnderAttack(const int square, const bool iswhiteside){
    
    return true;
}

void Board::printSquaresUnderAttack(const bool iswhiteside){
    std::cout << "\n\n       BOARD:\n\n";
    for (int rank = 7; rank >= 0; rank--){
        for (int file = 0; file < 8; file++){
            if (!file){
                std::cout << rowsTOranks[rank] << "  ";
            }
            std::cout << (isSquareUnderAttack(rank * 16 + file, iswhiteside) ? "x" : ".") << " ";
        }      
        std::cout << "\n";  
    }
    std::cout << "\n   ";
    for (int file = 0; file < 8; file++){
        std::cout << colsTOfiles[file] << " ";
    }
    std::cout << "\n\n";
}

chess::Board::Board()
{
    board.resize(128);
    for(int square = 0; square < 128; square++){
        if ((square & 0x88)){
            // Out of the board
            board[square] = Piece(-1);
        }else{
            // Empty square
            board[square] = Piece(0);
        }
    }

    iswhitetomove = false;

    whiteKingside = false;
    whiteQueenside = false;
    blackKingside = false;
    blackQueenside = false;

    enpassantSquare = -1;
}

chess::Board::~Board()
{
}

void Board::printBoard()
{   
    std::cout << "\n\n       BOARD:\n\n";
    for (int rank = 7; rank >= 0; rank--){
        for (int file = 0; file < 8; file++){
            if (!file){
                std::cout << rowsTOranks[rank] << "  ";
            }
            if (rank * 16 + file == enpassantSquare){
                std::cout << "S" << " ";
                continue;
            }
            std::cout << pieceToChar[this->board[rank * 16 + file].getCode()]<< " ";
        }      
        std::cout << "\n";  
    }
    std::cout << "\n   ";
    for (int file = 0; file < 8; file++){
        std::cout << colsTOfiles[file] << " ";
    }
    std::cout << "\n\n";

    std::cout << "Is white to move? "<< this->iswhitetomove << "\n";
    std::cout << "Castlings Rights:\n";
    std::cout << "\nFor white pieces:\n";
    std::cout << "King side: " << this->whiteKingside << "\n";
    std::cout << "Queen side: " << this->whiteQueenside << "\n";
    std::cout << "\nFor white pieces:\n";
    std::cout << "King side: " << this->blackKingside << "\n";
    std::cout << "Queen side: " << this->blackQueenside << "\n";
    
    //enpassant target square
    if( enpassantSquare != -1){
        std::cout << "\nEnpassant position: "<< colsTOfiles[enpassantSquare & 7] << rowsTOranks[enpassantSquare >> 4] << "\n";
        std::cout << "Enpassant squre: " << enpassantSquare << "\n";

    }
}

void Board::SetFen(const std::string &fen)
{
    std::vector<std::string> sections = split(fen, ' ');    

    // for the first section - pieces position
    int file = 0;
    int rank = 7;
    for (const char& symbol : sections[0]){
        if (symbol == '/'){
            file = 0;
            rank--;
        }else{
            if (isdigit(symbol)) {
                file += (int) (symbol - '0');
                continue;
            } else{
                int piececolor = (isupper(symbol)) ?  WHITEn : BLACKn;
                int pieceType = SymbolToType[ tolower(symbol) ];
                this->board[16*rank + file] =  Piece(pieceType, piececolor);
                pieces.push_back(16*rank + file);
                (piececolor == WHITEn) ? white_pieces.push_back(16*rank + file) : black_pieces.push_back(16*rank + file);
                file++;
            }

        }
    }
    // for the second section - iswhitetomove
    iswhitetomove = (sections[1] == "w");

    // check castlings rights
    whiteKingside = containsChar(sections[2], 'K');
    whiteQueenside = containsChar(sections[2], 'Q');
    blackKingside = containsChar(sections[2], 'k');
    blackQueenside = containsChar(sections[2], 'q');

    // enpassant targetsquare 
    if ( sections[3] != "-"){
        enpassantSquare = getBoardPosition(sections[3]);
    }
}

int Board::getBoardPosition(const std::string &s){
    int rank;
    int file;
    for (const char& c : s){
        if(isdigit(c)){
            rank = ranksTOrows[c];
        }else{
            file = filesTOcols[c];
        }
    }
    return (16*rank + file);
}

Piece Board::getPiece(const int &square)
{
    return board[square];
}

void Board::generatePseudoLegalMoves(){
    
    std::list<int>& currpieces = (iswhitetomove) ? white_pieces : black_pieces;
    for(int square : currpieces){
        switch (board[square].getType())
        {
        case QUEEN:
            std::cout << "\n\nQUEEN at square: " << square << "\n\n";
            get_pseudo_moves(square, queen_offsets ,pseudolegalMoves);
            continue;

        case ROOK:
            std::cout << "\n\nROOK at square: " << square << "\n\n";
            get_pseudo_moves(square, rook_offsets ,pseudolegalMoves);
            continue;

        case BISHOP:
            std::cout << "\n\nBISHOP at square: " << square << "\n\n";
            get_pseudo_moves(square, bishop_offsets ,pseudolegalMoves);
            continue;

        case KNIGHT: //bugado
            std::cout << "\n\nKNIGHT at square: " << square << "\n\n";
            getKnightMoves(square, knight_offsets ,pseudolegalMoves);
            continue; 

        case KING: //bugaod
            std::cout << "\n\nKING at square: " << square << "\n\n";
            getKingMoves(square, king_offsets ,pseudolegalMoves);
            continue; 

        case PAWN:
            getPawnMoves(square, pseudolegalMoves);
            continue; 

        default:
            continue;
        }

    }
}

// for sliding pieces
void Board::get_pseudo_moves(const int &square, std::vector<int> &offsets_, std::list<Move> &targets){
    int fromcolor = board[square].getColor();

    for (int offsets : offsets_){
        int currsquare = square;
        int i = 1;
        while (1)
        {
            int currsquare = (square + offsets*i);
            if(( currsquare & 0x88)){ // if it's out of the board
                break;
            }

            if ( board[currsquare].isEmpty() ){ // if it's empty
                targets.push_back(Move(square, currsquare,EMPTY,false,false,false,false));
                i++;
                std::cout << "" << currsquare << "\n";
                continue;
            }
            if ( board[currsquare].getColor() == fromcolor ){ // if it's a friendly piece
                i++;
                break;
            }
            if (board[currsquare].getColor() != fromcolor){ // if it's enemy piece
                std::cout << "" << currsquare << "\n";
                targets.push_back(Move(square, currsquare,EMPTY,true,false,false,false));
                i++;
                break;
            }
            i++;
        }      
    }
}

void Board::getKnightMoves(const int &square, std::vector<int> &offsets_, std::list<Move> &targets){
    int fromcolor = board[square].getColor();
    for (int offsets : offsets_){
        int currsquare = (square + offsets);
        if(( currsquare & 0x88)){ // if it's out of the board
            continue;;
        }

        if ( board[currsquare].isEmpty() ){ // if it's empty
            targets.push_back(Move(square, currsquare,EMPTY,false,false,false,false));
            continue;
        }
        if (board[currsquare].getColor() != fromcolor){ // if it's enemy piece
            targets.push_back(Move(square, currsquare,EMPTY,true,false,false,false));
            continue;
        }              
    }
}

void Board::getKingMoves(const int &square, std::vector<int> &offsets_, std::list<Move> &targets){
    // TODO: castling
    int fromcolor = board[square].getColor();
    for (int offsets : offsets_){
        int currsquare = (square + offsets);
        if(( currsquare & 0x88)){ // if it's out of the board
            continue;;
        }

        if ( board[currsquare].isEmpty() ){ // if it's empty
            targets.push_back(Move(square, currsquare,EMPTY,false,false,false,false));
            continue;
        }
        if (board[currsquare].getColor() != fromcolor){ // if it's enemy piece
            targets.push_back(Move(square, currsquare,EMPTY,true,false,false,false));
            continue;
        }              
    }
}

void Board::getPawnMoves(const int &square, std::list<Move> &targets){
    int fromcolor = board[square].getColor();
    
    // TODO : enppassant e otimizar logica(se possivel - acho que sim)

    std::vector<int>& offsets_ = (iswhitetomove) ? white_pawn_offsets : black_pawn_offsets;

    for (int offsets : offsets_){ 
        int currsquare = (square + offsets);
        if(( currsquare & 0x88)){ // if it's out of the board
            continue;
        }
        if ( board[currsquare].isEmpty() && offsets == offsets_[0] ){ // if it's empty
            targets.push_back(Move(square, currsquare,EMPTY,false,false,false,false));
            if (((square>>4) == 1)|| ((square>>4) == 6)){ //first white pawn move
                currsquare = square + 2 * offsets;
                if ( board[currsquare].isEmpty() ){
                    targets.push_back(Move(square, currsquare,EMPTY,false,true,false,false));  
                    continue;  
                }
            } //pawn move capture
        }
        if((board[currsquare].isEmpty() == false ) && (board[currsquare].getColor()!=fromcolor) && ((offsets==offsets_[1])||(offsets==offsets_[2]))){
            targets.push_back(Move(square, currsquare,EMPTY,false,true,false,false));    
        } 
    }
}

std::list<int> Board::getPossibleDestinations(int square){
    std::list<int> lista; 
    for(Move m : pseudolegalMoves){
        if ( m.getStart() == square){
            lista.push_back(m.getTarget());
        }
    }         
    
    return lista;
}

}