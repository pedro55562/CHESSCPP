#include "move.hpp"

namespace chess
{ 

Move::Move(int source, int target, int promotedPiece, int capture, bool doublePawnPush, bool enpassant, bool castling)
{   
    move = (source)|                // Source square
        ((target << 7))|            // Target square
        ((promotedPiece << 14))|    // Promoted piece
        (capture << 18)|            // Captured piece
        (doublePawnPush << 21)|     // Double pawn push flag
        (enpassant << 22)|          // Enpassant flag
        (castling << 23);           // Castling flag
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

int Move::getCapture() const
{
    return (move & 0x1C0000)>>18;
}

bool Move::getDoublePawnPush() const
{
    return move & 0x00200000;
}

bool Move::getEnpassant() const
{
    return move & 0x00400000;
}

bool Move::getCastling() const
{
    return move & 0x00800000;
}

}