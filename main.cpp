#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>

#include "include/piece.hpp"
#include "include/board.hpp"
#include "include/constants.hpp"
#include "include/move.hpp"
#include "include/ChessRenderer.hpp"


int main() {
    chess::Board board;
    board.SetFen("8/1n3B2/8/3Q4/8/1p6/6P1/8 w - - 0 1");
    board.pseudoMoveGenerator();

    chess::ChessRenderer grapghicboard = chess::ChessRenderer(board);
    board.printBoard();  
    while (grapghicboard.shouldClose() == false){
        grapghicboard.render();
        int k = grapghicboard.handleMouseInput();
        if (k == -1)
            break;

        grapghicboard.updateSelectedPiece(k);
        
        int k1 = grapghicboard.handleMouseInput();
        if (k1 == -1)
            break;    

        
    }
    

    return 0;
}