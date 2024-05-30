#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>

#include "piece.hpp"
#include "board.hpp"
#include "constants.hpp"
#include "move.hpp"

int main() {
    chess::Board game;
    game.SetFen("8/8/8/8/3Q4/8/8/8 b - - 0 1");
    game.printBoard();  
    game.printSquaresUnderAttack();
    return 0;
}