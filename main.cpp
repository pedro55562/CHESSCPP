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
    game.SetFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -");
    game.printBoard();  

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