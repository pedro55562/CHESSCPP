#ifndef CASTLE_HPP
#define CASTLE_HPP


#include <cstdint>

/*
    Enconding:
        whiteKingside   0000 0001 << 0
        whiteQueenside  0000 0010 << 1 
        blackKingside   0000 0100 << 2
        blackQueenside  0000 1000 << 3

    

*/

namespace chess
{ 

class Castle
{
private:
    int8_t castle;

public:
    Castle(bool whiteKingside, bool whiteQueenside, bool blackKingside, bool blackQueenside);

    Castle();

    bool getWhiteKingside();

    bool getWhiteQueenside();

    bool getBlackKingside();

    bool getBlackQueenside();


};

}
#endif