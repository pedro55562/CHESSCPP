#ifndef MOVE_HPP
#define MOVE_HPP


#include <cstdint>

//talvez:
// TODO: adicionar opção de peça capturada(tipo e cor)
// TODO: adicionar opção de cor da peça movida

/*
    Enconding moves into a 32 integer:

    We need to keep track of:

    -> source square            0000 0000 0000 0000 0000 0000 0111 1111 = 0x00007F 
    -> target square            0000 0000 0000 0000 0011 1111 1000 0000 = 0x003F80 << 7
    -> promoted piece           0000 0000 0000 0011 1100 0000 0000 0000 = 0x03C000 << 14
    -> captured piece(type)     0000 0000 0001 1100 0000 0000 0000 0000 = 0x1C0000 << 18
    -> double pown push         0000 0000 0010 0000 0000 0000 0000 0000 = 0x00200000         << 21
    -> enpassant flag           0000 0000 0100 0000 0000 0000 0000 0000 = 0x00400000         << 22
    -> castling                 0000 0000 1000 0000 0000 0000 0000 0000 = 0x00800000        << 23

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
    Move(int source, int target, int promotedPiece, int capture, bool doublePawnPush
                    , bool enpassant , bool castling                                 );

    
    
    
    ~Move();

    int getStart() const;

    int getTarget() const;

    int getPromotedPiece() const;

    int getCapture() const;

    bool getDoublePawnPush() const;

    bool getEnpassant() const;

    bool getCastling() const;
};

}

#endif