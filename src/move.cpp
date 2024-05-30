#include "move.hpp"

namespace chess
{ 

Move::Move(int source, int target, int promotedPiece, bool capture, bool doublePawnPush, bool enpassant, bool castling)
{   
    move = (source)|                // Source square
        ((target << 7))|            // Target square
        ((promotedPiece << 14))|    // Promoted piece
        (capture << 18)|            // Capture flag
        (doublePawnPush << 19)|     // Double pawn push flag
        (enpassant << 20)|          // Enpassant flag
        (castling << 21);           // Castling flag
}

Move::~Move()
{
}

int Move::getStart() const
{
    return move & 0x00007F;
}

int Move::getTarget() const
{
    return (move & 0x003F80)>>7;
}

int Move::getPromotedPiece() const
{
    return (move & 0x03C000)>>14;
}

bool Move::getCapture() const
{
    return move & 0x040000;
}

bool Move::getDoublePawnPush() const
{
    return move & 0x080000;
}

bool Move::getEnpassant() const
{
    return move & 0x100000;
}

bool Move::getCastling() const
{
    return move & 0x200000;
}

}