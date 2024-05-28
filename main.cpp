#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>

#include "piece.hpp"
#include "board.hpp"
#include "constants.hpp"



int main() {
    chess::Board game;
    game.SetFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -");
    game.printBoard();  
    game.printSquaresUnderAttack(1);

    chess::Move move = chess::Move(12,108,chess::BISHOP,true,true,true,true);
    
    std::cout << "\nStart: "<< move.getStart() << "\n";
    std::cout << "Target: "<< move.getTarget() << "\n";
    std::cout << "Promoted piece: "<< move.getPromotedPiece() << "\n";
    std::cout << "capture: "<< move.getCapture() << "\n";
    std::cout << "pawnpush: "<< move.getDoublePawnPush() << "\n";
    std::cout << "enpassant: "<< move.getEnpassant() << "\n";
    std::cout << "castling: "<< move.getCastling() << "\n";


    std::cout <<"\n\n";

    std::cout << sizeof(chess::Piece) << "\n";

    return 0;
}