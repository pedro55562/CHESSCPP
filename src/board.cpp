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
    std::cout << "\nCastlings Rights:\n";
    std::cout << "\nFor white pieces:\n";
    std::cout << "King side: " << this->whiteKingside << "\n";
    std::cout << "Queen side: " << this->whiteQueenside << "\n";
    std::cout << "\nFor black pieces:\n";
    std::cout << "King side: " << this->blackKingside << "\n";
    std::cout << "Queen side: " << this->blackQueenside << "\n";
    
    //enpassant target square
    if( enpassantSquare != -1){
        std::cout << "\n\nEnpassant position: "<< colsTOfiles[enpassantSquare & 7] << rowsTOranks[enpassantSquare >> 4] << "\n";
        std::cout << "Enpassant square: " << enpassantSquare << "\n";

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
    }else{
        enpassantSquare = -1;
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

void Board::pseudoMoveGenerator(){
    std::list<int>& myPieces = (iswhitetomove) ? white_pieces : black_pieces;

    for(int square : myPieces){
        Piece piece = board[square];
        //Pawn moves
        if(piece.isType(PAWN)){
            int promoted_rank = iswhitetomove ? 7 : 0;
            int double_push_rank = iswhitetomove ? 1 : 6;
            int push_offset = (iswhitetomove) ? 16: -16;
            std::vector<int> capture_offsets = (iswhitetomove) ? std::vector<int>{17, 15} : std::vector<int>{-17, -15};

            //quite moves - pawn promotions - double pawn push
            if(!((square+push_offset) & 0x88)){// if it's on the board
                if (board[square+push_offset].isEmpty()){ 
                    //normal pawn move
                    pseudolegalMoves.push_back(Move(square,square+push_offset,EMPTY,false,false,false,false));

                    //pawn promotion
                    if (((square+push_offset)>>4) == promoted_rank){
                        pseudolegalMoves.push_back(Move(square,square+push_offset,QUEEN,false,false,false,false));
                        pseudolegalMoves.push_back(Move(square,square+push_offset,KNIGHT,false,false,false,false));
                        pseudolegalMoves.push_back(Move(square,square+push_offset,BISHOP,false,false,false,false));
                        pseudolegalMoves.push_back(Move(square,square+push_offset,ROOK,false,false,false,false));
                    }
                    //double push
                    else if(board[square+2*push_offset].isEmpty() && ((square>>4) == double_push_rank)){
                        pseudolegalMoves.push_back(Move(square,square+2*push_offset,EMPTY,false,true,false,false)); 
                    }
                }
            }
            //capture moves - pawn promotion
            for(int offset : capture_offsets){
                if(!((square+offset) & 0x88)){
                    if( (!board[square+offset].isEmpty()) && (!board[square+offset].isColor(board[square].getColor()))){
                        if( ((square+offset)>>4) == promoted_rank ){
                            pseudolegalMoves.push_back(Move(square,square+offset,QUEEN ,true,false,false,false));
                            pseudolegalMoves.push_back(Move(square,square+offset,KNIGHT,true,false,false,false));
                            pseudolegalMoves.push_back(Move(square,square+offset,BISHOP,true,false,false,false));
                            pseudolegalMoves.push_back(Move(square,square+offset,ROOK  ,true,false,false,false));                           
                        }else{
                            pseudolegalMoves.push_back(Move(square,square+offset,EMPTY,false,false,false,false));
                        }
                    }
                }
            }
            //enpassant captures
            if (enpassantSquare != -1){
                int offset = square - enpassantSquare;
                if(abs(offset) == 17 || abs(offset) == 15){
                    int enemy_piece_pos =enpassantSquare + ((iswhitetomove)? -16 : 16);
                    if(!((enpassantSquare+offset) & 0x88)){
                        if( (!board[enemy_piece_pos].isEmpty()) && (!board[enemy_piece_pos].isColor(board[square].getColor())) && ((enpassantSquare+offset) == square)){
                            pseudolegalMoves.push_back(Move(square,enpassantSquare,EMPTY,false,false,true,false));
                        }
                    }
                }
            }
        }

        //Leaper piece moves
        //Knight:
        if(piece.isType(KNIGHT)){
            for(int offset : knight_offsets){
                if(!((square+offset) & 0x88)){
                    if(board[square+offset].isEmpty()){
                        pseudolegalMoves.push_back(Move(square,square+offset,EMPTY,false,false,false,false));
                    }
                    if (!board[square+offset].isColor(board[square].getColor()) ){
                        pseudolegalMoves.push_back(Move(square,square+offset,EMPTY,true,false,false,false));
                    }
                }
            }
        }
        //KING:
        if(piece.isType(KING)){
            for(int offset : king_offsets){
                if(!((square+offset) & 0x88)){
                    if(board[square+offset].isEmpty()){
                        pseudolegalMoves.push_back(Move(square,square+offset,EMPTY,false,false,false,false));
                    }
                    if (!board[square+offset].isColor(board[square].getColor()) ){
                        pseudolegalMoves.push_back(Move(square,square+offset,EMPTY,true,false,false,false));
                    }
                }
            }
            //Castling:
            int kingsquare = (iswhitetomove) ? 4: 116;
            bool kingside   = (iswhitetomove) ? whiteKingside  : blackKingside;
            bool queenside  = (iswhitetomove) ? whiteQueenside : blackQueenside;
            // if it's king side:
            if(queenside){
                if(board[kingsquare+1].isEmpty() && board[kingsquare+2].isEmpty()){
                    if((!isSquareUnderAttack(kingsquare+1)) && (!isSquareUnderAttack(kingsquare+2))){
                        pseudolegalMoves.push_back(Move(kingsquare,kingsquare+2,false,false,false,false,true));
                    }
                }
            }
            // if it's queen side:
            if(kingside){
                if(board[kingsquare-1].isEmpty() && board[kingsquare-2].isEmpty() && board[kingsquare-3].isEmpty()){
                    if((!isSquareUnderAttack(kingsquare-1)) && (!isSquareUnderAttack(kingsquare-2))){
                        pseudolegalMoves.push_back(Move(kingsquare,kingsquare-2,false,false,false,false,true));
                    }
                }
            }

        }
        //Slider pieces moves - Rooks, bishops, queens
        //Rooks:
        if(piece.isType(ROOK)){
            for(int offset : rook_offsets){
                int target = square+offset;
                while(!(target&0x88)){
                    if(!board[target].isEmpty()){
                        //enemypiece:
                        if(!board[target].isColor(piece.getColor())){
                            pseudolegalMoves.push_back(Move(square,target,EMPTY,true,false,false,false));
                            break;
                        //friendly piece
                        }
                        break;
                    }else{//empty
                        pseudolegalMoves.push_back(Move(square,target,EMPTY,false,false,false,false));
                        target+=offset;
                        continue;
                    }
                    
                }
            }
        }

        //Bishops:
        if(piece.isType(BISHOP)){
            for(int offset : bishop_offsets){
                int target = square+offset;
                while(!(target&0x88)){
                    if(!board[target].isEmpty()){
                        //enemypiece:
                        if(!board[target].isColor(piece.getColor())){
                            pseudolegalMoves.push_back(Move(square,target,EMPTY,true,false,false,false));
                            break;
                        //friendly piece
                        }
                        break;
                    }else{//empty
                        pseudolegalMoves.push_back(Move(square,target,EMPTY,false,false,false,false));
                        target+=offset;
                        continue;
                    }
                    
                }
            }
        }
    
        if(piece.isType(QUEEN)){
            for(int offset : queen_offsets){
                int target = square+offset;
                while(!(target&0x88)){
                    if(!board[target].isEmpty()){
                        //enemypiece:
                        if(!board[target].isColor(piece.getColor())){
                            pseudolegalMoves.push_back(Move(square,target,EMPTY,true,false,false,false));
                            break;
                        //friendly piece
                        }
                        break;
                    }else{//empty
                        pseudolegalMoves.push_back(Move(square,target,EMPTY,false,false,false,false));
                        target+=offset;
                        continue;
                    }
                    
                }
            }
        }
    }
}

void Board::getLegalMoves(){
    //por agora:
    legalMoves = pseudolegalMoves;
}

void Board::makeMove(Move m){
    int piece_color = board[m.getTarget()].getColor();

    //making the move:
    board[m.getTarget()] = board[m.getStart()];
    board[m.getStart()] = Piece();

    //if the piece is a king
    if(board[m.getTarget()].isType(KING)){
        if (piece_color == WHITEn){
            whiteking = m.getStart();
        }else{
            blacking = m.getTarget();
        }
    }


    enpassantSquare = -1;
    //if it's double pawn push
    if(m.getDoublePawnPush()){
        enpassantSquare = m.getStart() + ((iswhitetomove) ? 16 : -16 );
    }

    //if it's castling

    //if it's enpassant

    //dar update em lista de pieces
    std::list<int>& mypieces = (iswhitetomove) ? white_pieces : black_pieces;
    for(int& i : mypieces){
        if(i == m.getStart()){
            i = m.getTarget();
        }
    }
    //if it's capture
    if(m.getCapture()){
        std::list<int>& enemy = (!iswhitetomove) ? white_pieces : black_pieces;
        for(std::list<int>::iterator it = enemy.begin(); it != enemy.end(); ++it){ // removendo da lista e indo do comeco
            if(*it == m.getTarget()){
                enemy.erase(it);
                break;
            }
        }
    }
}

void Board::movePiece(int start, int target){
    for(Move m : legalMoves){
        if(m.getStart() == start && m.getTarget() == target){
            if(m.getPromotedPiece() == EMPTY){
                makeMove(m);
                return;
            }   
            if (m.getPromotedPiece() == QUEEN){
                makeMove(m);
                return;
            }else{
                continue;
            }
        }
    }
    return;
}
}