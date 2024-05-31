#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>

#include "include/piece.hpp"
#include "include/constants.hpp"
#include "include/move.hpp"
#include "include/ChessRenderer.hpp"


void teste(){
    std::string defaultFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    chess::Board board;
    board.SetFen("r3k2r/8/6P1/8/8/1p6/8/R3K2R w KQkq - 0 1");
    board.getLegalMoves();

    chess::ChessRenderer grapghicboard = chess::ChessRenderer(board);
    while (grapghicboard.shouldClose() == false){
        
        if(board.returnMoveMade()){
            board.getLegalMoves();
            board.setMoveMade();
        }

        board.printBoard();  


        grapghicboard.render();
        int k = grapghicboard.handleMouseInput();
        if (k == -1)
            break;
        if (k == -2){
            board.unMakeMove();
            continue;
        }

        if(board.returnMoveMade()){
            board.getLegalMoves();
            board.setMoveMade();
        }
        
        grapghicboard.updateSelectedPiece(k);
        
        int k1 = grapghicboard.handleMouseInput();
        if (k1 == -1)
            break;    
        if (k == -2){
            board.unMakeMove();
            continue;        
        }

        grapghicboard.updateSelectedPiece(k);


        board.movePiece(k,k1);

        
    }
    


}

int main() {

    teste();


    return 0;
}