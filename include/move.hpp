#ifndef MOVE_HPP
#define MOVE_HPP


#include <cstdint>

/*
    Enconding moves into a 32 integer:

    We need to keep track of:

    -> source square        0000 0000 0000 0000 0111 1111 = 0x00007F 
    -> target square        0000 0000 0011 1111 1000 0000 = 0x003F80 << 7
    -> promoted piece       0000 0011 1100 0000 0000 0000 = 0x03C000 << 14
    -> capture flag         0000 0100 0000 0000 0000 0000 = 0x040000 << 18
    -> double pown push     0000 1000 0000 0000 0000 0000 = 0x080000 << 19
    -> enpassant flag       0001 0000 0000 0000 0000 0000 = 0x100000 << 20
    -> castling             0010 0000 0000 0000 0000 0000 = 0x200000 << 21


    Promoted piece encoding:
    0b0000 - 0  none-promotion
	0b0101 - 5	knight-promotion
	0b0100 - 4	bishop-promotion
	0b0011 - 3  rook-promotion
	0b0010 - 2	queen-promotion
*/

namespace chess
{ 

class Move
{
private:
    int32_t move;

public:
    Move(int source, int target, int promotedPiece, bool capture, bool doublePawnPush
                    , bool enpassant , bool castling                                 );

    
    
    
    ~Move();

    int getStart();

    int getTarget();

    int getPromotedPiece();

    bool getCapture();

    bool getDoublePawnPush();

    bool getEnpassant();

    bool getCastling();
};

}

#endif