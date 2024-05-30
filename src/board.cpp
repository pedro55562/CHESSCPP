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


// if your square is attacked by the opponent
bool Board::isSquareUnderAttack(const int square){

    // TARGET SQUARE = THE SQUARE THAT THE ATTACK MAY COMES FROM
    
    //pawn attacks:
    //black pawns are attacking
    if (iswhitetomove){
        //if the targer square is onboard
        if(!((square+17) & 0x88) &&  board[square+17].isPiece(PAWN | BLACKn) ){
             return true;
        }
        else if(!((square+15) & 0x88) &&  board[square+15].isPiece(PAWN | BLACKn) ){
             return true;
        } 

    //white pawns attacks
    }if (!iswhitetomove){
        //if the targer square is onboard
        if(!((square-17) & 0x88) &&  board[square-17].isPiece(PAWN | WHITEn) ){
             return true;
        }
        else if(!((square-15) & 0x88) &&  board[square-15].isPiece(PAWN | WHITEn) ){
             return true;
        } 
    }

    // KNIGHT:
    //Black knights are attacking
    if(iswhitetomove){
        for(int offset : knight_offsets){
            if(!((square+offset) & 0x88) &&  board[square+offset].isPiece(KNIGHT | BLACKn) ){
                return true;
            }
        }
    }if (!iswhitetomove){
        for(int offset : knight_offsets){
            if(!((square+offset) & 0x88) &&  board[square+offset].isPiece(KNIGHT | WHITEn) ){
                return true;
            }
        }
    }

    // KNIGHT:
    //Black king are attacking
    if(iswhitetomove){
        for(int offset : king_offsets){
            if(!((square+offset) & 0x88) &&  board[square+offset].isPiece(KING | BLACKn) ){
                return true;
            }
        }
    }if (!iswhitetomove){
        for(int offset : king_offsets){
            if(!((square+offset) & 0x88) &&  board[square+offset].isPiece(KING | WHITEn) ){
                return true;
            }
        }
    }

    //BISHOP AND QUEEN
    //black attacking
    if(iswhitetomove){
        for(int offset : bishop_offsets){
            int targetsquare = square + offset;
            while (!(targetsquare&0x88)){
                if ( board[targetsquare].isPiece( QUEEN | BLACKn) ){
                    return true;
                }if ( board[targetsquare].isPiece( BISHOP | BLACKn) ){
                    return true;
                }if (!board[targetsquare].isEmpty() ){
                    break;
                }
                targetsquare += offset;
            }
            
        }
    }// white attacking
    if (!iswhitetomove){
        for(int offset : bishop_offsets){
            int targetsquare = square + offset;
            while (!(targetsquare&0x88)){
                if ( board[targetsquare].isPiece( QUEEN | WHITEn) ){
                    return true;
                }
                if (board[targetsquare].isPiece( BISHOP | WHITEn) ){
                    return true;
                }
                if (!board[targetsquare].isEmpty() ){
                    break;
                }
                targetsquare += offset;
            } 
        }
    }    


    //ROOK AND QUEEN
    if(iswhitetomove){
        for(int offset : rook_offsets){
            int targetsquare = square + offset;
            while (!(targetsquare&0x88)){
                if ( board[targetsquare].isPiece( QUEEN | BLACKn) ){
                    return true;
                }
                if ( board[targetsquare].isPiece( ROOK | BLACKn) ){
                    return true;
                }
                if (!board[targetsquare].isEmpty() ){
                    break;
                }
                targetsquare += offset;
            }
            
        }
    }// white attacking
    if (!iswhitetomove){
        for(int offset : rook_offsets){
            int targetsquare = square + offset;
            while (!(targetsquare&0x88)){
                if ( board[targetsquare].isPiece( QUEEN | WHITEn) ){
                    return true;
                }
                if (board[targetsquare].isPiece( ROOK | WHITEn) ){
                    return true;
                }
                if (!board[targetsquare].isEmpty() ){
                    break;
                }
                targetsquare += offset;
            } 
        }
    } 
    return false;
}

void Board::printSquaresUnderAttack(){
    std::cout << "\n\n       BOARD:\n\n";
    for (int rank = 7; rank >= 0; rank--){
        for (int file = 0; file < 8; file++){
            if (!file){
                std::cout << rowsTOranks[rank] << "  ";
            }
            std::cout << (isSquareUnderAttack(rank * 16 + file) ? "x" : ".") << " ";
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
            if (isSquareUnderAttack(rank * 16 + file)){
                std::cout << "x" << " ";
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


}