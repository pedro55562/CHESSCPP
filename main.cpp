#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>

#include "piece.hpp"
#include "board.hpp"
#include "constants.hpp"
#include "ChessRenderer.hpp"


int main() {
    chess::Board game;
    game.SetFen("rnbqkbnr/ppp1pppp/5P2/8/8/3p4/PPPPP1PP/RNBQKBNR b KQkq - 0 1");
    game.printBoard();  
    game.generatePseudoLegalMoves();
    chess::ChessRenderer graphic(game);

    while (!graphic.shouldClose())
    {
        graphic.render();
        int s = graphic.handleMouseInput();
        graphic.updateSelectedPiece(s);
    }
    

    std::cout << sizeof(chess::Piece) << "\n";

    return 0;
}