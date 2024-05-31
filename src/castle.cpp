#ifndef MOVE_HPP
#define MOVE_HPP


#include <cstdint>
#include "castle.hpp"

/*
    Enconding:
        whiteKingside   0001 
        whiteQueenside  0010 << 1 
        blackKingside   0100 << 2
        blackQueenside  1000 << 3

    

*/

namespace chess
{ 

Castle::Castle(bool whiteKingside, bool whiteQueenside, bool blackKingside, bool blackQueenside){
    castle = (whiteKingside)|(whiteQueenside << 1)|(blackKingside << 2)|(blackQueenside << 3);
}

Castle::Castle(){
    castle = 0;
}

bool Castle::getWhiteKingside()
{
    return castle & 0b0001;
}

bool Castle::getWhiteQueenside()
{
    return castle & 0b0010;
}

bool Castle::getBlackKingside()
{
    return castle & 0b0100;
}

bool Castle::getBlackQueenside()
{
    return castle & 0b1000;
}

}
#endif